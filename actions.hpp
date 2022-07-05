#include <string>

struct Action{
  std::string name = "";
  std::string description = "";
  int value1 = 0;
  int value2 = 0;
  
  Action();
  Action(std::string, std::string, int, int);
};

static const Action null_action;

static const Action grow = Action("Pump Up", "The warrior's blood heats as it fills with rage. Increases his strength by 10 points for some time.", 10, 350);
static const Action stun = Action("Ice Prison", "The mage condenses the cold air around the tip of his staff as he fires the blow at the enemy, freezing him for some time rounds.", 1, 350);
static const Action za_knife = Action("Poisoned Knife", "The rogue soaks his blade in an oriental poison, delivering a slash that weaken the foe's defense for some time.", 10, 350);
static const Action big_heal = Action("Grand Heal", "The healer channels his inner energy to close even the deadliest of wounds. Heal the target in 40 HP", 40, 0);
static const Action za_arrow = Action("Poisoned Arrow", "The archer holds his breath, aims his arrow well, and hits an enemy vital point, disorienting him for two rounds.", 1, 350);
static const Action weaken = Action("Lullaby", "The bard plays a song that make his opponent fatigued, making it deal less damage.", 10, 350);
