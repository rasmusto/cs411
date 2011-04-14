#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xa28daf12, "module_layout" },
	{ 0xa212a7a2, "elv_register" },
	{ 0xe2a896be, "elv_dispatch_sort" },
	{ 0xb3decf43, "kmem_cache_alloc" },
	{ 0xd391e6e0, "malloc_sizes" },
	{ 0x37a0cba, "kfree" },
	{ 0xc16e21e7, "elv_unregister" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

