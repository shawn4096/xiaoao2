// lutianshu.c


#include <ansi.h>;
/*
string *sword_skill = ({ 
"taiji-jian","damo-jian","fumo-jian","jinshe-jianfa","qingmang-jian","yuxiao-jian",
"yunu-jianfa","songshan-jian","murong-jianfa","huashan-jianfa", "duanjia-jianfa",
"songfeng-jian","qingyin-jian","shangqing-jian",
"huifeng-jian","liangyi-jian","quanzhen-jianfa" }); 

string *blade_skill = ({ 
"cibei-dao","fanliangyi-dao","liuhe-daofa","murong-daofa","qingmang-jian","wenjia-daofa", 
"shandian-daofa","xiuluo-dao","xuanxu-daofa", "yanxing-daofa",}); 
string *spear_skill = ({ "zhong-qiang","yangjia-qiang","hujia-qiang","bawang-qiang" }); 
*/
int do_copy(object me)
{
        object ob;
        int i;
        ob = this_object();

        if(!me) ob->unconcious();
          
        i = me->query("max_pot") - 80 ;
		if (this_object()->query("id")=="hua tiegan")
		{
			i = me->query("max_pot") - 70 ;
		}
		if (this_object()->query("id")=="shuidai")
		{
			i = me->query("max_pot") - 60 ;
		}
		
		if (this_object()->query("id")=="shuidai")
		{
			i = me->query("max_pot") - 50 ;
		}
        i=i+random(20);

		if(i < 550) i = 550;
//基本参数设定
        ob->set("combat_exp",(int) me->query("combat_exp")*3/2);
		ob->set("max_qi", (int)me->query("max_qi")*2); 
		ob->set("eff_qi",(int) me->query("max_qi")*2);

        ob->set("max_jing", (int)me->query("max_jing")/2*3); 
        ob->set("eff_jing", (int)me->query("eff_jing")/2*3);
		ob->set("max_jingli", (int)me->query("max_jingli")/2*3);
        ob->set("eff_jingli",(int) me->query("jingli")/2*3);
        ob->set("max_neili", (int)me->query("max_neili")*2);
		ob->set("neili", (int)me->query("max_neili")*2);

        ob->set("jiali", 250);
        ob->reincarnate(); 
//基本参数设定


        ob->set_skill("force", i);
        ob->set_skill("cuff", i);
        ob->set_skill("dodge", i);
        ob->set_skill("parry", i);
		ob->set_skill("strike", i);
        ob->set_skill("leg", i);
        ob->set_skill("hand", i);
        ob->set_skill("claw", i);
        ob->set_skill("finger", i);

        ob->set_skill("spear", i);
        ob->set_skill("sword", i);
        ob->set_skill("blade", i);
		ob->set_skill(ob->query_skill_mapped("force"),i);
		ob->set_skill(ob->query_skill_mapped("dodge"),i);
		if (ob->query_skill_mapped("cuff"))
			ob->set_skill(ob->query_skill_mapped("cuff"),i);
		if (ob->query_skill_mapped("strike"))
			ob->set_skill(ob->query_skill_mapped("strike"),i);
		if (ob->query_skill_mapped("hand"))
			ob->set_skill(ob->query_skill_mapped("hand"),i);

		
		if (ob->query_skill_mapped("blade"))
			ob->set_skill(ob->query_skill_mapped("blade"),i);
		if (ob->query_skill_mapped("spear"))
			ob->set_skill(ob->query_skill_mapped("spear"),i);
		if (ob->query_skill_mapped("sword"))
			ob->set_skill(ob->query_skill_mapped("sword"),i);

        command("stare " + me->query("id"));
        command("say 武林淫贼，邪恶无比，人人得而诛之。\n" );
		//remove_call_out("checking");
        call_out("checking", 1, me, ob);
        ob->set("victim", me->query("id"));
        ob->set_temp("target", me->query("id"));

        return 1;
}

int do_kill(object ob)
{
	object me = this_object();
	if(!ob) return 0;
	//增加判断是否自己的npc
	if (me->query_temp("target")!=ob->query("id"))
		return notify_fail("他和你无冤无仇，你干嘛要乱杀无辜？\n");
	
	::do_kill(ob);
}
