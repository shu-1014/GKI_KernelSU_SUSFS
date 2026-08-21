#include <linux/init.h>
#include <linux/module.h>
#include <linux/utsname.h>
#include <linux/string.h>
#include <linux/mm.h>

static int __init fake_ver_init(void)
{
    char *ver = utsname()->release;
    // !!! 总长度严格28字节，不够末尾补空格，不要加长！
    const char fake[] = ""5.15.180‑a13‑shu‑xiao‑leng";
    size_t len = sizeof(fake) - 1;

    // 解除rodata只读保护
    set_memory_rw((unsigned long)ver, 1);

    memcpy(ver, fake, len);

    // 改回只读
    set_memory_ro((unsigned long)ver, 1);

    pr_info("fake_version: now release = %s\n", utsname()->release);
    return 0;
}
early_initcall(fake_ver_init);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("xiaoleng");
MODULE_DESCRIPTION("Fake uname‑r for 5.15 GKI");
