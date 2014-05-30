<?php

global $input1;

function debug(Neuron $neuron, $data = null, $target = null, $tree = null, $prefix = '')
{
    global $input1;

    $type = 'Output';
    if ($neuron->branch() instanceof Peripheral) {
        $type = 'Input' . ($neuron === $input1 ? '1' : '2');
    } elseif ($neuron->branch() instanceof Bias) {
        $type = 'Bias';
    } elseif (count($neuron->branch()->synapses()) && $prefix !== '') {
        $type = 'Hidden';
    }

    $function = end(explode('\\', get_class($neuron->outputFunction())));
    $output = $data ? ': ' . $neuron->output($data) : '';
    $error = $derivative = '';
    if ($type == 'Hidden' || $type == 'Output') {
        $error = $tree ? ' (e: ' . $tree->error($neuron, $data, $target) . ')' : '';
        $derivative = $data ? ' (>: ' . $neuron->derivative($data) . ')' : '';
    }
    echo $prefix, $type, '(', $function, ')', $output, $error, $derivative, "\n";

    foreach ($neuron->branch()->synapses() as $i => $synapse) {
        $delta = $tree ? ' (d: ' . $tree->delta($synapse, $data, $target) . ')' : '';
        echo $prefix, '  Synapse ', $i, ' => ', $synapse->weight(), $delta, "\n";
        debug($synapse->neuron(), $data, $target, $tree, $prefix . '    ');
    }
}

function rand_range($min, $max)
{
    return $min + ((rand() / getrandmax()) * ($max - $min));
}
