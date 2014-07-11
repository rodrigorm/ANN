
extern zend_class_entry *ann_branch_ce;

ZEPHIR_INIT_CLASS(Ann_Branch);

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_branch_output, 0, 0, 1)
	ZEND_ARG_INFO(0, activation)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(ann_branch_method_entry) {
	PHP_ABSTRACT_ME(Ann_Branch, output, arginfo_ann_branch_output)
  PHP_FE_END
};
