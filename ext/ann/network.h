
extern zend_class_entry *ann_network_ce;

ZEPHIR_INIT_CLASS(Ann_Network);

PHP_METHOD(Ann_Network, __construct);
PHP_METHOD(Ann_Network, calculate);
PHP_METHOD(Ann_Network, train);
PHP_METHOD(Ann_Network, activate);
PHP_METHOD(Ann_Network, accept);
PHP_METHOD(Ann_Network, request);
PHP_METHOD(Ann_Network, response);
PHP_METHOD(Ann_Network, create);

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_network___construct, 0, 0, 2)
	ZEND_ARG_INFO(0, inputs)
	ZEND_ARG_INFO(0, outputs)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_network_calculate, 0, 0, 1)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_network_train, 0, 0, 4)
	ZEND_ARG_INFO(0, trainer)
	ZEND_ARG_INFO(0, data)
	ZEND_ARG_INFO(0, targets)
	ZEND_ARG_INFO(0, factor)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_network_activate, 0, 0, 1)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_network_accept, 0, 0, 1)
	ZEND_ARG_INFO(0, visitor)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_network_request, 0, 0, 1)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_network_response, 0, 0, 1)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_network_create, 0, 0, 1)
	ZEND_ARG_INFO(0, nodes)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(ann_network_method_entry) {
	PHP_ME(Ann_Network, __construct, arginfo_ann_network___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Ann_Network, calculate, arginfo_ann_network_calculate, ZEND_ACC_PUBLIC)
	PHP_ME(Ann_Network, train, arginfo_ann_network_train, ZEND_ACC_PUBLIC)
	PHP_ME(Ann_Network, activate, arginfo_ann_network_activate, ZEND_ACC_PRIVATE)
	PHP_ME(Ann_Network, accept, arginfo_ann_network_accept, ZEND_ACC_PUBLIC)
	PHP_ME(Ann_Network, request, arginfo_ann_network_request, ZEND_ACC_PRIVATE)
	PHP_ME(Ann_Network, response, arginfo_ann_network_response, ZEND_ACC_PRIVATE)
	PHP_ME(Ann_Network, create, arginfo_ann_network_create, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
  PHP_FE_END
};
