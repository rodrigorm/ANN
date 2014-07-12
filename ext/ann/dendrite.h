
extern zend_class_entry *ann_dendrite_ce;

ZEPHIR_INIT_CLASS(Ann_Dendrite);

PHP_METHOD(Ann_Dendrite, __construct);
PHP_METHOD(Ann_Dendrite, output);
PHP_METHOD(Ann_Dendrite, activate);
PHP_METHOD(Ann_Dendrite, accept);

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_dendrite___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, synapses)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_dendrite_output, 0, 0, 1)
	ZEND_ARG_INFO(0, activation)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_dendrite_activate, 0, 0, 1)
	ZEND_ARG_INFO(0, activation)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_dendrite_accept, 0, 0, 1)
	ZEND_ARG_INFO(0, visitor)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(ann_dendrite_method_entry) {
	PHP_ME(Ann_Dendrite, __construct, arginfo_ann_dendrite___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Ann_Dendrite, output, arginfo_ann_dendrite_output, ZEND_ACC_PUBLIC)
	PHP_ME(Ann_Dendrite, activate, arginfo_ann_dendrite_activate, ZEND_ACC_PUBLIC)
	PHP_ME(Ann_Dendrite, accept, arginfo_ann_dendrite_accept, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
