
extern zend_class_entry *ann_visitee_ce;

ZEPHIR_INIT_CLASS(Ann_Visitee);

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_visitee_accept, 0, 0, 1)
	ZEND_ARG_INFO(0, visitor)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(ann_visitee_method_entry) {
	PHP_ABSTRACT_ME(Ann_Visitee, accept, arginfo_ann_visitee_accept)
  PHP_FE_END
};
