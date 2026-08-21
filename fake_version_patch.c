#include <linux/init.h>
#include <linux/module.h>
#include <linux/utsname.h>
#include <linux/string.h>

static int __init fake_ver_init(void)
{
    // 原地覆盖，字符长度必须完全一致！
    char *ver = utsname()->release;
    // 示例，总长度和原字符串字节数对齐，多余用空格补齐
    const char fake[] = "6.6.89‑FAKE‑MYKERNEL  ";
    memcpy(ver, fake, sizeof(fake)-1);
    pr_info("fake_version: kernel release changed to: %s\n", utsname()->release);
    return 0;
}
early_initcall(fake_ver_init);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("xiaoleng");
MODULE_DESCRIPTION("Runtime fake uname‑r version");
