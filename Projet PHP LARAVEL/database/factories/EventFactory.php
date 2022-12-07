<?php

namespace Database\Factories;

use App\Models\Event;
use Illuminate\Database\Eloquent\Factories\Factory;
use Illuminate\Support\Facades\DB;

class EventFactory extends Factory
{
    /**
     * The name of the factory's corresponding model.
     *
     * @var string
     */
    protected $model = Event::class;

    /**
     * Define the model's default state.
     *
     * @return array
     */
    public function definition()
    {
        $usersID = DB::table('users')->pluck('id');
        return [
            'title' => $this->faker->realText($maxNbChars = 20, $indexSize = 2),
            'message' => $this->faker->realText($maxNbChars = 200, $indexSize = 2),
            'date' => $this->faker->dateTimeBetween($startDate = '-1 years'),
            'lieu' => $this->faker->address,
            'nbparticipant'=>$this->faker->numberBetween($min = 0, $max = 100),
            'prix'=>$this->faker->numberBetween($min=0, $max = 100),
        ];
    }
}
