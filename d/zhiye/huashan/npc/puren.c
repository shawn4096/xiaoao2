// NPC: /d/huashan/npc/puren.c
// Date: Look 99/03/25
// Modify By Looklove@SJ 2000/1/7 for add job
// Lklv Modify at 2001.10.18
// By Spiderii@ty 增加送饭功能
#include <ansi.h>
inherit NPC;
string ask_over();
string ask_food();
string* names = ({
	FOOD_D("baozi"),
	FOOD_D("cuishan"),
	FOOD_D("douhua"),
	FOOD_D("doufu"),
	FOOD_D("guoba"),
	FOOD_D("jitui"),
	FOOD_D("liji"),
	FOOD_D("liyu"),
	FOOD_D("niurou"),
	FOOD_D("peanut"),
	FOOD_D("sansi"),
	FOOD_D("yaoliu"),
});
void create()
{
	set_name("仆人", ({ "pu ren", "puren",}));
	set("long","一个烧饭扫地的仆人\n");
	set("gender", "男性");
	set("age", 26);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str", 23);
	set("int", 23);
	set("con", 24);
	set("dex", 28);

	set("max_qi", 300);
	set("max_jing", 180);
	set("neili", 300);
	set("max_neili", 300);
	set("eff_jingli", 180);

	set("jiali", 5);
	set("combat_exp", 5000);
	set("score", 50);

	set_skill("unarmed", 20);
	set("inquiry", ([
	      "柴禾" : (: ask_over :),
	      "砍材" : (: ask_over :),
	      "caihe" : (: ask_over :),
             "食物" : (:ask_food:),

	]));
	setup();
	carry_object(ARMOR_D("armor/cloth"))->wear();
}

string ask_over()
{
	int exp,pot;
	object me;
	me = this_player();

	//if ((int)me->query("combat_exp") >= 100000)
		//return "虽然厨房缺柴禾，可是这些事还是让我们下人来做吧。\n";
	if (me->query("shen") < 10000)
		return "你眼露凶光, 最近是不是做了什么坏事？ ";
	if (!me->query_temp("hs/kc_job")||!me->query_temp("kc_job/ok"))
		return "你六师兄刚才来说，要帮我找几个弟子去砍柴，你去不去？去就告诉他一声。\n";

	me->delete_temp("hs/kc_job");
	me->delete_temp("kc_job");

	exp = me->query("max_pot")+random(100);
	exp=exp/2;
	if (me->query("combat_exp")<1000000)
	{	
		exp = me->add_exp_combat(exp,this_object(),"华山砍柴");
	}
	pot = 50 + random(50);

	//me->add("combat_exp",exp);
	me->add("shen",exp*3/4);
	me->add("potential",pot);
	//if(me->query("potential") > me->query("max_pot"))
	//	me->set("potential", me->query("max_pot"));
		me->improve_skill("force",me->query("int")*2);
		
	me->add("job_time/华山砍柴",1);
	me->apply_condition("job_busy",6);
    if (random(me->query("job_time/华山砍柴"))>800 && random(me->query("kar"))>25 &&!me->query("quest/hs/dichuan"))
    {
		message_vision("仆人对$N微微一笑说道：“岳掌门让我替他考察门下弟子的忠诚度，你经过考核已经成为华山的嫡传弟子。”\n",me);
		me->set("quest/hs/dichuan",1);
		me->set("title","华山气宗嫡传弟子");
    }
	message_vision("$N大声对仆人说道：“你要的柴禾我都砍了，堆在朝阳峰，需要的话你找人去取。”\n",me);
	if (me->query("combat_exp")<1000000)
	{
		tell_object(me,HIM" 你得到了：\n" +	chinese_number(exp) + "点实战经验\n"+chinese_number(pot) + "点潜能。\n"NOR);
	}else
		tell_object(me,HIM" 你得到了：\n" +chinese_number(pot) + "点潜能。\n"NOR);

	command("ok "+me->query("id"));

	return "先堆着吧，等我要用的时候我就去取。\n";
}
string ask_food()
{
	object ob1,ob2;
	object me;
	me=this_player();
       	if ((me->query("food")*10/me->max_water_capacity())>8)
		return "你怎么吃饱了还想要？";
               ob1 = new(FOOD_D("rice"));
	        ob2 = new(names[random(sizeof(names))]);
	        if( clonep(ob2) && clonep(ob1))
	        {
	        	message_vision(HIC"\n仆人说道：饭菜已经准备好了，快趁热吃吧。\n" NOR, me);
	        	ob1->move(me);
	        	ob2->move(me);
		}
}

