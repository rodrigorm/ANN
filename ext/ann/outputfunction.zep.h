
extern zend_class_entry *ann_outputfunction_ce;

ZEPHIR_INIT_CLASS(Ann_OutputFunction);

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_outputfunction_forward, 0, 0, 1)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_outputfunction_derivative, 0, 0, 1)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(ann_outputfunction_method_entry) {
	PHP_ABSTRACT_ME(Ann_OutputFunction, forward, arginfo_ann_outputfunction_forward)
	PHP_ABSTRACT_ME(Ann_OutputFunction, derivative, arginfo_ann_outputfunction_derivative)
  PHP_FE_END
};
