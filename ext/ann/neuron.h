
extern zend_class_entry *ann_neuron_ce;

ZEPHIR_INIT_CLASS(Ann_Neuron);

PHP_METHOD(Ann_Neuron, __construct);
PHP_METHOD(Ann_Neuron, output);
PHP_METHOD(Ann_Neuron, activate);
PHP_METHOD(Ann_Neuron, derivative);
PHP_METHOD(Ann_Neuron, accept);

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_neuron___construct, 0, 0, 2)
	ZEND_ARG_INFO(0, branch)
	ZEND_ARG_INFO(0, outputFunction)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_neuron_output, 0, 0, 1)
	ZEND_ARG_INFO(0, activation)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_neuron_activate, 0, 0, 1)
	ZEND_ARG_INFO(0, activation)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_neuron_derivative, 0, 0, 1)
	ZEND_ARG_INFO(0, activation)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_neuron_accept, 0, 0, 1)
	ZEND_ARG_INFO(0, visitor)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(ann_neuron_method_entry) {
	PHP_ME(Ann_Neuron, __construct, arginfo_ann_neuron___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Ann_Neuron, output, arginfo_ann_neuron_output, ZEND_ACC_PUBLIC)
	PHP_ME(Ann_Neuron, activate, arginfo_ann_neuron_activate, ZEND_ACC_PUBLIC)
	PHP_ME(Ann_Neuron, derivative, arginfo_ann_neuron_derivative, ZEND_ACC_PUBLIC)
	PHP_ME(Ann_Neuron, accept, arginfo_ann_neuron_accept, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
