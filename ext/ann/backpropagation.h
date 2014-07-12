
extern zend_class_entry *ann_backpropagation_ce;

ZEPHIR_INIT_CLASS(Ann_BackPropagation);

PHP_METHOD(Ann_BackPropagation, __construct);
PHP_METHOD(Ann_BackPropagation, teach);
PHP_METHOD(Ann_BackPropagation, visitNetwork);
PHP_METHOD(Ann_BackPropagation, visitNeuron);
PHP_METHOD(Ann_BackPropagation, visitPeripheral);
PHP_METHOD(Ann_BackPropagation, visitBias);
PHP_METHOD(Ann_BackPropagation, visitDendrite);
PHP_METHOD(Ann_BackPropagation, visitSynapse);
PHP_METHOD(Ann_BackPropagation, set);
PHP_METHOD(Ann_BackPropagation, get);
PHP_METHOD(Ann_BackPropagation, getAll);

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_backpropagation___construct, 0, 0, 3)
	ZEND_ARG_INFO(0, delta)
	ZEND_ARG_INFO(0, trainset)
	ZEND_ARG_INFO(0, factor)
	ZEND_ARG_INFO(0, objects)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_backpropagation_teach, 0, 0, 1)
	ZEND_ARG_INFO(0, network)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_backpropagation_visitnetwork, 0, 0, 3)
	ZEND_ARG_INFO(0, network)
	ZEND_ARG_INFO(0, inputs)
	ZEND_ARG_INFO(0, outputs)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_backpropagation_visitneuron, 0, 0, 3)
	ZEND_ARG_INFO(0, neuron)
	ZEND_ARG_INFO(0, branch)
	ZEND_ARG_INFO(0, function)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_backpropagation_visitperipheral, 0, 0, 1)
	ZEND_ARG_INFO(0, peripheral)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_backpropagation_visitbias, 0, 0, 1)
	ZEND_ARG_INFO(0, bias)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_backpropagation_visitdendrite, 0, 0, 2)
	ZEND_ARG_INFO(0, dendrite)
	ZEND_ARG_INFO(0, synapses)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_backpropagation_visitsynapse, 0, 0, 3)
	ZEND_ARG_INFO(0, synapse)
	ZEND_ARG_INFO(0, neuron)
	ZEND_ARG_INFO(0, weight)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_backpropagation_set, 0, 0, 2)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_backpropagation_get, 0, 0, 1)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_backpropagation_getall, 0, 0, 1)
	ZEND_ARG_INFO(0, keys)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(ann_backpropagation_method_entry) {
	PHP_ME(Ann_BackPropagation, __construct, arginfo_ann_backpropagation___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Ann_BackPropagation, teach, arginfo_ann_backpropagation_teach, ZEND_ACC_PUBLIC)
	PHP_ME(Ann_BackPropagation, visitNetwork, arginfo_ann_backpropagation_visitnetwork, ZEND_ACC_PUBLIC)
	PHP_ME(Ann_BackPropagation, visitNeuron, arginfo_ann_backpropagation_visitneuron, ZEND_ACC_PUBLIC)
	PHP_ME(Ann_BackPropagation, visitPeripheral, arginfo_ann_backpropagation_visitperipheral, ZEND_ACC_PUBLIC)
	PHP_ME(Ann_BackPropagation, visitBias, arginfo_ann_backpropagation_visitbias, ZEND_ACC_PUBLIC)
	PHP_ME(Ann_BackPropagation, visitDendrite, arginfo_ann_backpropagation_visitdendrite, ZEND_ACC_PUBLIC)
	PHP_ME(Ann_BackPropagation, visitSynapse, arginfo_ann_backpropagation_visitsynapse, ZEND_ACC_PUBLIC)
	PHP_ME(Ann_BackPropagation, set, arginfo_ann_backpropagation_set, ZEND_ACC_PRIVATE)
	PHP_ME(Ann_BackPropagation, get, arginfo_ann_backpropagation_get, ZEND_ACC_PRIVATE)
	PHP_ME(Ann_BackPropagation, getAll, arginfo_ann_backpropagation_getall, ZEND_ACC_PRIVATE)
  PHP_FE_END
};
