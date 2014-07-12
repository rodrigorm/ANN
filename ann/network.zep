
namespace Ann;

use Ann\Neuron;
use Ann\OutputFunction\Linear;
use Ann\OutputFunction\Sigmoid;
use Ann\Trainset;
use Ann\Visitee;
use Ann\Visitor;
use Ann\Activation;

class Network implements Visitee
{
    private $inputs;
    private $outputs;

    public function __construct(array $inputs, array $outputs)
    {
        let $this->inputs = $inputs;
        let $this->outputs = $outputs;
    }

    public function calculate(array $data)
    {
		var $activation, $response, $output, $temp;
        let $activation = $this->activate($data);

        let $response = new Output();

        for $output in $this->outputs {
            let $temp = $response->set($output, $activation->output($output));
			let $response = $temp;
        }

        return $response;
    }

    public function train(<Trainer> $trainer, array $data, array $targets, $factor)
    {
		var $activation, $response;
        let $activation = $this->activate($data);
        let $response = $this->response($targets);
        return $trainer->train($this, new Trainset($activation, $response), $factor);
    }

    private function activate(array $data)
    {
		var $activation, $output;
        let $activation = new Activation($this->request($data), new Output());

        for $output in $this->outputs {
            let $activation = $output->output($activation);
        }

        return $activation;
    }

    public function accept(<Visitor> $visitor)
    {
        return $visitor->visitNetwork($this, $this->inputs, $this->outputs);
    }

    private function request(array $data)
    {
		var $result, $i, $value, $temp;
        let $result = new Input();

        for $i, $value in $data {
            let $temp = $result->set($this->inputs[$i], $value);
			let $result = $temp;
        }

        return $result;
    }

    private function response(array $data)
    {
		var $result, $i, $value, $temp;
        let $result = new Output();

        for $i, $value in $data {
            let $temp = $result->set($this->outputs[$i], $value);
			let $result = $temp;
        }

        return $result;
    }

    public static function create(array $nodes)
    {
		var $inputs, $layer, $layers, $count, $i, $j, $branch, $function, $synapses, $neuron;
        let $inputs = [];
        let $layers = [];

        for $count in $nodes {
            let $i = count($layers);
            let $layers[$i] = [];

            for $j in range(0, $count) {
                if ($i == count($nodes) - 1 && $j == $count) {
                    continue;
                }

                let $branch = new Peripheral();
                let $function = new Sigmoid();

                if (count($nodes) == 2) {
                    let $function = new Linear();
                }

                if ($j == $count) {
                    let $branch = new Bias();
                    let $function = new Linear();
                } else {
					if ($i == 0) {
						let $function = new Linear();
					} else {
						let $synapses = [];

						for $neuron in $layers[$i - 1] {
							let $synapses[] = new Synapse(
								$neuron,
								-1.0 + (rand(0, 100) / 50.0)
							);
						}

						let $branch = new Dendrite($synapses);
					}
				}

                if ($branch instanceof Peripheral) {
                    let $inputs[] = $branch;
                }

                let $neuron = new Neuron(
                    $branch,
                    $function
                );
				let $layer = $layers[$i];
                let $layer[$j] = $neuron;
				let $layers[$i] = $layer;
            }
        }

        return new Network(
            $inputs,
            $layers[count($layers) - 1]
        );
    }
}
