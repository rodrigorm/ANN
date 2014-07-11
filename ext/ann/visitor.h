
extern zend_class_entry *ann_visitor_ce;

ZEPHIR_INIT_CLASS(Ann_Visitor);

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_visitor_visitnetwork, 0, 0, 3)
	ZEND_ARG_INFO(0, network)
	ZEND_ARG_INFO(0, inputs)
	ZEND_ARG_INFO(0, outputs)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_visitor_visitneuron, 0, 0, 3)
	ZEND_ARG_INFO(0, neuron)
	ZEND_ARG_INFO(0, branch)
	ZEND_ARG_INFO(0, function)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_visitor_visitperipheral, 0, 0, 1)
	ZEND_ARG_INFO(0, peripheral)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_visitor_visitbias, 0, 0, 1)
	ZEND_ARG_INFO(0, bias)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_visitor_visitdendrite, 0, 0, 2)
	ZEND_ARG_INFO(0, dendrite)
	ZEND_ARG_INFO(0, synapses)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_visitor_visitsynapse, 0, 0, 3)
	ZEND_ARG_INFO(0, synapse)
	ZEND_ARG_INFO(0, neuron)
	ZEND_ARG_INFO(0, weight)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(ann_visitor_method_entry) {
	PHP_ABSTRACT_ME(Ann_Visitor, visitNetwork, arginfo_ann_visitor_visitnetwork)
	PHP_ABSTRACT_ME(Ann_Visitor, visitNeuron, arginfo_ann_visitor_visitneuron)
	PHP_ABSTRACT_ME(Ann_Visitor, visitPeripheral, arginfo_ann_visitor_visitperipheral)
	PHP_ABSTRACT_ME(Ann_Visitor, visitBias, arginfo_ann_visitor_visitbias)
	PHP_ABSTRACT_ME(Ann_Visitor, visitDendrite, arginfo_ann_visitor_visitdendrite)
	PHP_ABSTRACT_ME(Ann_Visitor, visitSynapse, arginfo_ann_visitor_visitsynapse)
  PHP_FE_END
};
