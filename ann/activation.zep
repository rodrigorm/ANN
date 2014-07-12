
namespace Ann;

use Ann\Input;
use Ann\Output;

class Activation
{
    private $input;
    private $output;

    public function __construct(<Input> $input, <Output> $output)
    {
        let $this->input = $input;
        let $this->output = $output;
    }

    public function activate($object)
    {
        if ($this->output->contains($object)) {
            return $this;
        }

        return $this->set($object, $object->activate($this));
    }

    public function input(<Peripheral> $peripheral)
    {
        return $this->input->get($peripheral);
    }

    public function set($key, $value)
    {
        return new self($this->input, $this->output->set($key, $value));
    }

    public function output($key)
    {
        return $this->output->get($key);
    }
}
