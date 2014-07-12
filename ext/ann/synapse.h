
extern zend_class_entry *ann_synapse_ce;

ZEPHIR_INIT_CLASS(Ann_Synapse);

PHP_METHOD(Ann_Synapse, __construct);
PHP_METHOD(Ann_Synapse, neuron);
PHP_METHOD(Ann_Synapse, weight);
PHP_METHOD(Ann_Synapse, output);
PHP_METHOD(Ann_Synapse, activate);
PHP_METHOD(Ann_Synapse, accept);

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_synapse___construct, 0, 0, 2)
	ZEND_ARG_INFO(0, neuron)
	ZEND_ARG_INFO(0, weight)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_synapse_output, 0, 0, 1)
	ZEND_ARG_INFO(0, activation)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_synapse_activate, 0, 0, 1)
	ZEND_ARG_INFO(0, activation)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_synapse_accept, 0, 0, 1)
	ZEND_ARG_INFO(0, visitor)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(ann_synapse_method_entry) {
	PHP_ME(Ann_Synapse, __construct, arginfo_ann_synapse___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Ann_Synapse, neuron, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Ann_Synapse, weight, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Ann_Synapse, output, arginfo_ann_synapse_output, ZEND_ACC_PUBLIC)
	PHP_ME(Ann_Synapse, activate, arginfo_ann_synapse_activate, ZEND_ACC_PUBLIC)
	PHP_ME(Ann_Synapse, accept, arginfo_ann_synapse_accept, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
