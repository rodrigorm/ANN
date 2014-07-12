
namespace Ann;

use Ann\Branch;
use Ann\Synapse;
use Ann\Activation;
use Ann\Visitor;

class Dendrite implements Branch
{
    private $synapses;

    public function __construct(array $synapses)
    {
        let $this->synapses = $synapses;
    }

    public function output(<Activation> $activation)
    {
		var $synapse;

        for $synapse in $this->synapses {
            let $activation = $synapse->output($activation);
        }

        return $activation->activate($this);
    }

    public function activate(<Activation> $activation)
    {
		var $result, $synapse;
        let $result = 0;

        for $synapse in $this->synapses {
            let $result += $activation->output($synapse);
        }

        return $result;
    }

    public function accept(<Visitor> $visitor)
    {
        return $visitor->visitDendrite($this, $this->synapses);
    }
}
