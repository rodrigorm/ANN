
namespace Ann;

use Ann\Branch;
use Ann\OutputFunction;
use Ann\Visitor;
use Ann\Visitee;
use Ann\Activation;

class Neuron implements Visitee
{
    private $branch;
    private $outputFunction;

    public function __construct(<Branch> $branch, <OutputFunction> $outputFunction)
    {
        let $this->branch = $branch;
        let $this->outputFunction = $outputFunction;
    }

    public function output(<Activation> $activation)
    {
        let $activation = $this->branch->output($activation);
        return $activation->activate($this);
    }

    public function activate(<Activation> $activation)
    {
        return $this->outputFunction->forward($activation->output($this->branch));
    }

    public function derivative(<Activation> $activation)
    {
        return $this->outputFunction->derivative($activation->output($this->branch));
    }

    public function accept(<Visitor> $visitor)
    {
        return $visitor->visitNeuron($this, $this->branch, $this->outputFunction);
    }
}
