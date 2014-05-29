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

        foreach ($this->inputs as $i => $input) {
            $request = $request->set($input->branch(), $data[$i]);
        }

        return $request;
    }

    public static function create($nodes)
    {
        $layers = array();
        $function = new Sigmoid();

        if (count($nodes) == 2) {
            $function = new Linear();
        }

        foreach ($nodes as $count) {
            $i = count($layers);
            $layers[$i] = array();

            for ($j = 0; $j < $count; $j++) {

                if ($i === 0) {
                    $neuron = new Neuron(
                        new Peripheral(),
                        $function
                    );
                } else {
                    $synapses = array();
                    foreach ($layers[$i -1] as $neuron) {
                        $synapses[] = new Synapse(
                            $neuron,
                            -1.0 + (rand(0, 100) / 50.0)
                        );
                    }

                    $neuron = new Neuron(
                        new Dendrite($synapses),
                        $function
                    );
                }
                $layers[$i][$j] = $neuron;
            }
        }

        return new Network(
            $layers[0],
            $layers[count($layers) - 1]
        );
    }
}
