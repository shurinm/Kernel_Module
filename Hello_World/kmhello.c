#include <linux/module.h>           // необходим для любого модуля ядра 
#include <linux/kernel.h>           // здесь находится определение KERN_ALERT 
#include <linux/init.h>             // здесь находятся определения макросов 

static int __init init_modul(void)
{
        printk(KERN_ALERT "Hello, world \n");
        return 0;                   // если вернется не 0, то считается как ошибка и модуль не будет загружен
}

static void __exit unloading_modul(void)
{
        printk(KERN_ALERT "Till, world \n");
}

module_init(init_modul);            // загружаем модуль
module_exit(unloading_modul);       // выгружаем модуль

MODULE_LICENSE("GPL");              // подпись лецензии

MODULE_AUTHOR("SHURINM");           // автор модуля 
MODULE_DESCRIPTION("TEST");         // назначение модуля 