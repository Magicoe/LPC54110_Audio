/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 */

#include <rtthread.h>

#ifdef RT_USING_FINSH
#include <finsh.h>
#include <shell.h>
#endif

#include "drv_msd_spi.h"
#include "rtdevice.h"
#ifdef RT_USING_DFS
#include <dfs_fs.h>
#include <dfs_init.h>
#include <dfs_elm.h>
#endif

extern int demo_init(void);

void rt_init_thread_entry(void* parameter)
{
    rt_thread_delay(2);
	
    msd_init("sd0", "spi10");
	
    /* Filesystem Initialization */
#if defined(RT_USING_DFS) && defined(RT_USING_DFS_ELMFAT)
    /* initialize the device file system */
    dfs_init();

    /* initialize the elm chan FatFS file system*/
    elm_init();
    
    /* mount sd card fat partition 1 as root directory */
    if (dfs_mount("sd0", "/", "elm", 0, 0) == 0) {
        rt_kprintf("File System initialized!\n");
    }
    else {
        rt_kprintf("File System initialzation failed!\n");
    }
#endif /* RT_USING_DFS && RT_USING_DFS_ELMFAT */

#ifdef RT_USING_I2C
    rt_i2c_core_init();
    rt_hw_i2c_init();
#endif

    codec_hw_init("i2c1"); 
		
	/* initialization finsh shell Component */
    finsh_system_init();

    demo_init();
}

int rt_application_init()
{
    rt_thread_t tid;

    tid = rt_thread_create("init", rt_init_thread_entry, RT_NULL, 2048, RT_THREAD_PRIORITY_MAX/3, 20);
    if (tid != RT_NULL)
        rt_thread_startup(tid);
		
    return 0;
}
