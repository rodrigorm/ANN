
namespace Ann;

use Ann\Synapse;
use SplObjectStorage;

class Delta
{
    private $synapses;

    public function __construct(<SplObjectStorage> $synapses = null)
    {
        let $this->synapses = $synapses ? $synapses : new SplObjectStorage();
    }

    public function set(<Synapse> $synapse, $delta)
    {
		var $synapses;
        let $synapses = clone $this->synapses;

        if ($synapses->contains($synapse)) {
            return $this;
        }

        $synapses->attach($synapse, $delta);

        return new self($synapses);
    }

    public function delta(<Synapse> $synapse)
    {
        return $this->synapses->offsetGet($synapse);
    }
}
