
extern zend_class_entry *ann_delta_ce;

ZEPHIR_INIT_CLASS(Ann_Delta);

PHP_METHOD(Ann_Delta, __construct);
PHP_METHOD(Ann_Delta, set);
PHP_METHOD(Ann_Delta, delta);

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_delta___construct, 0, 0, 0)
	ZEND_ARG_INFO(0, synapses)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_delta_set, 0, 0, 2)
	ZEND_ARG_INFO(0, synapse)
	ZEND_ARG_INFO(0, delta)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_delta_delta, 0, 0, 1)
	ZEND_ARG_INFO(0, synapse)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(ann_delta_method_entry) {
	PHP_ME(Ann_Delta, __construct, arginfo_ann_delta___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Ann_Delta, set, arginfo_ann_delta_set, ZEND_ACC_PUBLIC)
	PHP_ME(Ann_Delta, delta, arginfo_ann_delta_delta, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
