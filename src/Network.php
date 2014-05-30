<?php

namespace Ann;

use \Ann\Neuron;
use \Ann\OutputFunction\Linear;
use \Ann\OutputFunction\Sigmoid;

class Network
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
        $outputs = array();

        foreach ($this->outputs as $i => $output) {
            $outputs[] = $trainer->train($output, $request, $targets[$i], $factor);
        }

        foreach ($this->outputs as $i => $output) {
            if ($outputs[$i] !== $outputs) {
                return new self($this->inputs, $outputs);
            }
        }

        return $this;
    }

    private function request(array $data)
    {
        $request = new Input();

        foreach ($data as $i => $value) {
            $request = $request->set($this->inputs[$i]->branch(), $value);
        }

        return $request;
    }

    public static function create($nodes)
    {
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

                $neuron = new Neuron(
                    $branch,
                    $function
                );
                $layers[$i][$j] = $neuron;
            }
        }

        return new Network(
            $layers[0],
            $layers[count($layers) - 1]
        );
    }
}
