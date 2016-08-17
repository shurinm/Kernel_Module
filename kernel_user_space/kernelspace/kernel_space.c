#include "header/kernel_space.h"

MODULE_LICENSE("GPL");              // подпись лецензии

MODULE_AUTHOR("SHURINM");           // автор модуля 
MODULE_DESCRIPTION("DEV");          // назначение модуля 

#define DEVICE_NAME "my_device"
#define DEVICE_CLASS_NAME "my_class_chdev"

static dev_t                    dev;                // минорный и мажерный номер
static struct class             *class;             // класс устройства
static struct device            *device;            // созданое устройство
static struct cdev              cdev;               // зарегистрированное устройство
static struct file_operations   fops = {            // Перегружаемые функции
    .read = device_read,
    .write = device_write,
};


// инициализирует модуль. Запускается в момент загрузки в ядро
int init_module(void)
{
    // Получаем Свободный мажорный и первый минорный номера
    if (alloc_chrdev_region(&dev, 0, 1, DEVICE_NAME) < 0){
        printk(KERN_ERR "FAILED register_my_device_region\n");
        return -1;
    }

    // регистрируем устройство
    cdev_init(&cdev, &fops);
    if (cdev_add(&cdev, dev, 1) < 0){
        printk(KERN_ERR "FAILED my_device_add\n");
        return -1;
    }

    // создаем класс устройств
    class = class_create(THIS_MODULE, DEVICE_CLASS_NAME);
    if (IS_ERR(class)){
        printk(KERN_ERR "FAILED class_create\n");
        cdev_del(&cdev);
        unregister_chrdev_region(dev, 1);
        return -1;
    }
    // выставляем права
    class->devnode = device_devnode;

    // Создаем устройство
    device = device_create(class, NULL, dev, NULL, DEVICE_NAME);
    if (IS_ERR(device)){
        printk(KERN_ERR "FAILED device_create\n");
        class_destroy(class);
        cdev_del(&cdev);
        unregister_chrdev_region(dev, 1);
        return -1;
    }

    printk(KERN_ALERT "Driver get major %d\n", MAJOR(dev));
    return 0;
}

// финализация модуля. Удаляет все файлы устройств.  Запускается в момент выгрузки из ядра.
void cleanup_module(void)
{
    device_destroy(class, dev);
    class_destroy(class);
    cdev_del(&cdev);
    unregister_chrdev_region(dev, 1);
    printk(KERN_ALERT "Unregister for major number %d\n", MAJOR(dev));
}
// функция посылающая сообщение пользователю.
static ssize_t device_read(struct file *filep, char *buffer, size_t len,
                           loff_t *offset)
{
    char send_msg[] = {"Hello, user!\0"}; // Сообщение, возвращаемое пользователю
    ssize_t rbyte = 0;                    // Текущий считываемый байт

    while (send_msg[rbyte] != '\0' && rbyte < len){
        if (put_user(send_msg[rbyte++], buffer++)){
            return -1;
        }
    }
    printk(KERN_ALERT "User read from file\n");
    return rbyte - 1;
}

static ssize_t device_write(struct file *filep, const char *buffer, size_t len,
                            loff_t *offset)
{
    // Указатель на полученные от пользователя данные
    char *accepted_msg;    

    // выделяем динамически память по размеру полученного сообщения
    accepted_msg = kmalloc(len, GFP_KERNEL);
    if (!accepted_msg){
        printk(KERN_ERR "FAILED kmalloc\n");
        return -1;
    }
    if (!strncpy_from_user(accepted_msg, buffer, len)){
        printk(KERN_ERR "FAILED strncpy_from_user\n");
        return -1;
    }
    printk(KERN_ALERT "User write to file: %s\n", accepted_msg);
    kfree(accepted_msg);
    return 0;
}

static char *device_devnode(struct device *dev, umode_t *mode)
{
        if (!mode)
                return NULL;
        *mode = 0666;
        return NULL;
}