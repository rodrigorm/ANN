<?php

namespace Ann;

use \Ann\Neuron;
use \Ann\OutputFunction\Linear;
use \Ann\OutputFunction\Sigmoid;
use \Ann\Trainset;
use \Ann\Visitee;
use \Ann\Visitor;

class Network implements Visitee
{
    private $inputs;
    private $outputs;

    public function __construct(array $inputs, array $outputs)
    {
        $this->inputs = $inputs;
        $this->outputs = $outputs;
    }

    public function calculate(array $data)
    {
        $request = $this->request($data);
        $response = array();

        foreach ($this->outputs as $output) {
            $response[] = $output->output($request);
        }

        return $response;
    }

    public function train(Trainer $trainer, array $data, array $targets, $factor)
    {
        $request = $this->request($data);
        $response = $this->response($targets);
        return $trainer->train($this, new Trainset($request, $response), $factor);
    }

    public function accept(Visitor $visitor)
    {
        return $visitor->visitNetwork($this, $this->inputs, $this->outputs);
    }

    private function request(array $data)
    {
        $result = new Input();

        foreach ($data as $i => $value) {
            $result = $result->set($this->inputs[$i], $value);
        }

        return $result;
    }

    private function response(array $data)
    {
        $result = new Output();

        foreach ($data as $i => $value) {
            $result = $result->set($this->outputs[$i], $value);
        }

        return $result;
    }

    public static function create($nodes)
    {
        $inputs = array();
        $layers = array();

        foreach ($nodes as $count) {
            $i = count($layers);
            $layers[$i] = array();

            for ($j = 0; $j <= $count; $j++) {
                if ($i == count($nodes) - 1 && $j == $count) {
                    continue;
                }

                $branch = new Peripheral();
                $function = new Sigmoid();

                if (count($nodes) == 2) {
                    $function = new Linear();
                }

                if ($j == $count) {
                    $branch = new Bias();
                    $function = new Linear();
                } elseif ($i == 0) {
                    $function = new Linear();
                } else {
                    $synapses = array();

                    foreach ($layers[$i - 1] as $neuron) {
                        $synapses[] = new Synapse(
                            $neuron,
                            -1.0 + (rand(0, 100) / 50.0)
                        );
                    }

                    $branch = new Dendrite($synapses);
                }

                if ($branch instanceof Peripheral) {
                    $inputs[] = $branch;
                }

                $neuron = new Neuron(
                    $branch,
                    $function
                );
                $layers[$i][$j] = $neuron;
            }
        }

        return new Network(
            $inputs,
            $layers[count($layers) - 1]
        );
    }
}
