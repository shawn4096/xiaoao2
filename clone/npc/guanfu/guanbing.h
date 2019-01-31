// guanbing.h
// all include 官兵，武将 by Lklv 2002.1.18
// update by lsxk@hsbbs 增加自动报警，grin

#include <get_place.h>
#include <ansi.h>

void init()
{
	object ob;
	int level;
	string *pinji = ({ "内大臣", "九门提督","都统","副都统","副将","参将","巡捕统领","游击", "七都司", "守备", "九品千总","把总","巡捕头","巡捕" });
	::init();
	if (interactive(ob = this_player())
	 && living(this_object())
	 && ob->query_condition("killer")) {
		remove_call_out("kill_ob");
		call_out("kill_ob", 0, ob);
        }
		else if (ob->query("job_time/官府")>=10) {
			
			level=13;						
		if (ob->query("job_time/官府")>=10) level=12;
		if (ob->query("job_time/官府")>=100) level=11;
		if (ob->query("job_time/官府")>=500) level=10;
		if (ob->query("job_time/官府")>=1000) level=9;
		if (ob->query("job_time/官府")>=5000) level=8;
		if (ob->query("job_time/官府")>=10000) level=7;
		if (ob->query("job_time/官府")>=20000) level=6;
		if (ob->query("job_time/官府")>=40000) level=5;
		if (ob->query("job_time/官府")>=80000) level=4;
		if (ob->query("job_time/官府")>=100000) level=3;
		if (ob->query("job_time/官府")>=200000) level=2;
		if (ob->query("job_time/官府")>=400000) level=1;
		if (ob->query("job_time/官府")>=1000000) level=0;
		
			
        message_vision(HIY"官兵大声说道：“"+pinji[level]+" "+ob->query("name")+"大人在此，闲杂人等肃静!”\n"NOR, ob); 
		}
}

int accept_fight(object me)
{
    string p;
    object env = environment(this_object());

    p = get_place(file_name(env));
	if (!me) return 0;
    if(me->query("guanbing_chat_alarm"))
    message("system",HIY"【"+HIR+"官府警讯"+HIY+"】"+this_object()->query("name")+"("+this_object()->query("id")+")：各位注意！"+HIC+p+HIG+env->query("short")+HIY+"正遭到攻击！请附近平民迅速撤离危险地区！\n"NOR,users());

	if (query("id")=="wu jiang"){
		command("pei ");
		command("say 敢对朝廷命官无礼，今天让大爷我教训教训你！\n");
		fight_ob(me);
		return 1;
	}
	command("say 大爷我正想找人杀呐，今天算你倒霉。\n");
	if (!is_killing(me->query("id")))
		me->add_condition("killer", 5);
	kill_ob(me);
	return 1;
}

void kill_ob(object ob)
{
    string p;
    object env = environment(this_object());

    p = get_place(file_name(env));
	if (!ob) return;

    if(ob->query("guanbing_chat_alarm"))
    message("system",HIY"【"+HIR+"官府警讯"+HIY+"】"+this_object()->query("name")+"("+this_object()->query("id")+")：各位注意！"+HIC+p+HIG+env->query("short")+HIY+"正遭到攻击！请附近平民迅速撤离危险地区！\n"NOR,users());

	if (query("id") == "wu jiang")
		command("say 你！你！你！来人啊，给我拿下这个反贼！！！");
	else
		command("say 反贼！哪里走！！！");
	::kill_ob(ob);
}
