// shenghuo-xinfa.c 内功心法

inherit ITEM;

void create()
{
	set_name("圣火心法(下)", ({ "shenghuo xinfa", "xinfa" , "book" }));
	set_weight(600);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long", 
"这是一本手抄本，《圣火心法(下卷)》是张教主将明教的圣火神功和乾坤大挪移精华所整理而成。\n"
"里面密密麻麻的画了不少打坐吐呐的姿势。明教弟子可以读此领悟更多的诀窍\n"
		);				
		set("value", 1000);
		set("material", "paper");
		set("skill", ([
			"name":	"shenghuo-xinfa",	// name of the skill
			"exp_required":	0,	// minimum combat experience required
			"jing_cost":	50,	// jing cost every time study this
			"difficulty":	40,	// the base int to learn this skill
			"max_skill":	200	// the maximum level you can learn
		]) );
	}
}
