// By Spiderii@yt bt物品
#include <ansi.h>
inherit SPEC;

string *valid_type = ({
"force", "parry",  "dodge", "unarmed","claw",
"cuff",  "finger", "strike","hand",   "leg",
"sword", "blade",  "dagger","brush",  "spear",
"hook",  "stick",  "staff", "club",   "throwing",
"whip",  "axe",    "hammer","bow",
});

int sort_skill2(string sk) 
{
	return (SKILL_D(sk)->type() == "knowledge" && SKILL_D(sk)->type2() == "worker");
}

int sort_skill(string sk)
{
	return (SKILL_D(sk)->type() != "martial" && SKILL_D(sk)->type() != "array");
}

int sort_basic(string sk)
{
	return member_array(sk, valid_type)!=-1;
}

void create()
{
        set_name(HIR"悟道秘籍"HIW"(年卡特供)"NOR, ({ "mbook","book" }) );
        set_weight(10);
                set("unit", "本");
                set("long", "一本神奇秘籍。\n据说记载着天神闪电由武入道的体悟，阅读后能极大的提高你的武学技能。\n");
                set("material", "paper");
                set("no_drop", "这样东西极其珍贵，你还是考虑一下吧。\n");
                set("no_get", "这样东西不能离开那儿。\n");
   //             set("no_give", "这样东西极其珍贵，你还是考虑一下吧。\n");
                set_weight(100);
                set("value",30000000);
                set("treasure",1);
                set("degree",1);
                set("rest",2);
                set("flag","spec/myst");
                set("desc","阅读后能极大的提高武学技能。");
                set("credit",2500);  

       setup();
}
void init()
{
        add_action("do_open", "read");
}



int do_open(string arg)
{

 	
       object ob = this_player();
	mapping skl, lrn, map;
	string *sname, *mapped, *allskills, str = "";
	int i, j;


    if (!arg|| arg!="mbook")
            return notify_fail("你要读什么？\n");
            
     if (!ob->query("y-card-vip"))
            return notify_fail("你还不是年卡贵宾，暂时不能使用这个物品。\n");     
         
            
	if (!restrict()) {return notify_fail("本周你已经不能使用"+this_object()->query("name")+"了。\n");}

 skl = ob->query_skills();

 allskills  = sort_array( keys(skl), (: strcmp :) );


	sname=filter_array( allskills, (: sort_skill2 :) );

	allskills-=sname;

	sname=filter_array( allskills, (: sort_skill :) );
	allskills-=sname;

//这里是基本

	sname=filter_array( allskills, (: sort_basic :) );
	allskills-=sname;


	j = sizeof(sname);

         if(j>0)   for(i=0; i<j; i++) {
                             ob->set_skill(sname[i], ob->query("max_pot",1)-100);
                  }


//这里是特殊
	sname=allskills;

	j = sizeof(sname);
         if(j>0)   for(i=0; i<j; i++) {
                             ob->set_skill(sname[i], ob->query("max_pot",1)-100);
                  }
CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + ob->name(1) + "阅读了一次"HIR"悟道秘籍"HIC"，补满了所有的技能！\n"NOR);


	degree();
	return 1;

}

