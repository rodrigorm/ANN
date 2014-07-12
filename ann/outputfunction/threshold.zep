
namespace Ann\OutputFunction;

use Ann\OutputFunction;

class Threshold implements OutputFunction
{
    private $threshold;

    public function __construct($threshold = 1.0)
    {
        let $this->threshold = $threshold;
    }

    public function forward($value)
    {
        return ($value >= $this->threshold) ? 1.0 : 0.0;
    }

    public function derivative($value)
    {
        return 0;
    }
}
