
namespace Ann;

use Ann\Neuron;
use Ann\Trainset;
use Ann\BackPropagation\Node;
use Ann\Delta;
use Ann\Visitor;
use SplObjectStorage;

class BackPropagation implements Visitor
{
    private $delta;
    private $trainset;
    private $factor;
    private $objects;

    public function __construct(<Delta> $delta, <Trainset> $trainset, $factor, <SplObjectStorage> $objects = null)
    {
        let $this->delta = $delta;
        let $this->trainset = $trainset;
        let $this->factor = $factor;
        let $this->objects = $objects ? $objects : new SplObjectStorage();
    }

    public function teach(<Network> $network)
    {
        return $network->accept($this)->get($network);
    }

    public function visitNetwork(<Network> $network, array $inputs, array $outputs)
    {
		var $visitor, $neuron;
        let $visitor = $this;

        for $neuron in $outputs {
            let $visitor = $neuron->accept($this);
        }

        return $visitor->set($network, new Network($inputs, $visitor->getAll($outputs)));
    }

    public function visitNeuron(<Neuron> $neuron, <Branch> $branch, <OutputFunction> $function)
    {
		var $visitor;
        let $visitor = $branch->accept($this);
        return $visitor->set($neuron, new Neuron($visitor->get($branch), $function));
    }

    public function visitPeripheral(<Peripheral> $peripheral)
    {
        return $this;
    }

    public function visitBias(<Bias> $bias)
    {
        return $this;
    }

    public function visitDendrite(<Dendrite> $dendrite, array $synapses)
    {
		var $visitor, $synapse;
        let $visitor = $this;

        for $synapse in $synapses {
            let $visitor = $synapse->accept($visitor);
        }

        return $visitor->set($dendrite, new Dendrite($visitor->getAll($synapses)));
    }

    public function visitSynapse(<Synapse> $synapse, <Neuron> $neuron, $weight)
    {
		var $visitor, $delta, $weightChange;
        let $visitor = $neuron->accept($this);

        let $delta = $this->factor * $this->delta->delta($synapse);
        let $weightChange = $delta * $visitor->trainset->output($neuron);

        let $weight = $weight + $weightChange;

        return $visitor->set($synapse, new Synapse($visitor->get($neuron), $weight));
    }

    private function set($key, $value)
    {
        if ($this->objects->contains($key)) {
            return $this;
        }

		var $objects;
        let $objects = clone $this->objects;
        $objects->attach($key, $value);

        return new self($this->delta, $this->trainset, $this->factor, $objects);
    }

    private function get($key)
    {
        if ($this->objects->contains($key)) {
			return $this->objects->offsetGet($key);
        }

        return $key;
    }

    private function getAll($keys)
    {
		var $result, $key;
        let $result = [];

        for $key in $keys {
            let $result[] = $this->get($key);
        }

        return $result;
    }
}
