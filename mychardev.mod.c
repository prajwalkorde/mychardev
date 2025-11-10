#include <linux/module.h>
#include <linux/export-internal.h>
#include <linux/compiler.h>

MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x52b15b3b, "__unregister_chrdev" },
	{ 0x092a35a2, "_copy_from_user" },
	{ 0xd272d446, "__fentry__" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0xe8213e80, "_printk" },
	{ 0xa61fd7aa, "__check_object_size" },
	{ 0x092a35a2, "_copy_to_user" },
	{ 0x78a12d13, "__register_chrdev" },
	{ 0xd268ca91, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0x52b15b3b,
	0x092a35a2,
	0xd272d446,
	0xd272d446,
	0xe8213e80,
	0xa61fd7aa,
	0x092a35a2,
	0x78a12d13,
	0xd268ca91,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"__unregister_chrdev\0"
	"_copy_from_user\0"
	"__fentry__\0"
	"__x86_return_thunk\0"
	"_printk\0"
	"__check_object_size\0"
	"_copy_to_user\0"
	"__register_chrdev\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "DC7DBF270CF41B12A830A3C");
