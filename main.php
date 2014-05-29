<?php

require 'vendor/autoload.php';

use \Ann\Network;
use \Ann\Trainer;

$network = Network::create(array(2, 1));
$trainer = new Trainer();

$epoch = 0;
$iterations = 30;
$data = array(1.0, 1.0);
$target = array(rand(0, 100));

while ($epoch++ < $iterations) {
    $response = $network->calculate($data);
    echo 'Epoch ', $epoch, ': ', $response[0], "\t", ' (Error: ', abs($target[0] - $response[0]), ')', "\n";

    $factor = $epoch / $iterations;
    $network = $network->train($trainer, $data, $target, $factor);
}
