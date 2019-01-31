// sohu@xojh
//大理重新打造
inherit ITEM;
void create()
{
       set_name("内功精要", ({ "neigong jingyao", "book", "jingyao" }));
       set_weight(250);
       if( clonep() )
	   set_default_object(__FILE__);
       else {
	   set("unit", "本");
	   set("long", "这是一本很破旧的小册子，乃是大理皇家保存的心法精要，虽只剩下前几页，画着练气打坐的姿势。\n");
	   set("value", 500);
	   set("material", "paper");
       set("unique", 1);
       set("treasure", 1);
	   set("skill", ([
		"name":	"force",	 
		"exp_required":	3000, 
        "jing_cost":    10,   
		"difficulty":	20, 
		"max_skill":	50, 
	   ]));
	}
}
