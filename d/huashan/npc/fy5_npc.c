// tangfeng@SJ 2004
//inherit NPC;
// fy5_npc.c  修改成fengyi5 quest的npc  by lsxk@hsbbs  2007/8/29

inherit FIGHTER;
inherit F_UNIQUE;
#include <ansi.h>


//string *str_menpai = ({ "wd","hs","ss","gm","gb","tz","dls","sld","xx","mj","thd","kl"});	
//#include "/d/city/npc/skills_pfm.h";
void create()
{
   set_name(HIB"蒙面恶人"NOR, ({ "mengmian eren","eren","killer"}));
	set("long", "一位某门派弟子。\n");
   set("title", BLU"黑道高手"NOR);
	set("gender", "男性");
	set("age", 33);
	set("attitude", "peaceful");
   set("shen", -4000000-random(1000000));

   set("str", 30);
   set("int", 30);
   set("con", 30);
   set("dex", 30);

	set("max_qi", 30000);
	set("max_jing", 6000);
	set("eff_jingli",6000);
	set("neili", 20000);
	set("max_neili", 20000);
	set("jiali", 200);
	set("combat_exp", 2000000+random(1000000));
	set_skill("force", 70);
	set_skill("dodge", 80);
	set_skill("unarmed", 70);
	set_skill("parry", 80);
	set_skill("sword", 80);
	set_skill("cuff", 80);
	setup();
	carry_object(ARMOR_D("shoes"))->wear();
	carry_object(ARMOR_D("changshan"))->wear();
}
void init()
{
    object me,ob;  
    string good_skills;
    int i;     
    ::init();
    me = this_player();
    ob = this_object();
    if(ob->query("setok")) return;
	  if(!ob->query("party"))	ob->set("party",str_menpai[random(sizeof(str_menpai))]);  	 
    ob->copy_menpai(({ob->query("party")}),1,random(2),50+random(50));	//复制npc的门派武功，			
	  ob->copy_state();				//根据门派更新npc 的一些状态
		if (ob->query("f_skill2")) 
				good_skills=to_chinese(ob->query("f_skill"))+"和"+to_chinese(ob->query("f_skill2"));
		else	
				good_skills=to_chinese(ob->query("f_skill"));
   	ob->set("long",HIW+ob->query("family/family_name")+"高手，成名绝技："+good_skills+"。"NOR);
     if(!me->query("quest/hsjf/fy5/meet_killers")) 
	  {
		  ob->set_skills_level(400+random(100));
    	  return;
    }
        ob->set("long",HIY"这是一位黑道高手，武功已出神入化,鲜有对手！\n"NOR);
 		ob->set("setok",1);
	  i=me->query("max_pot");
	  if(i<350) i=350;
	  i=i-100;	
		ob->set_skills_level(i);
	  ob->set("max_neili",me->query("max_neili"));
  	ob->set("max_jingli",me->query("max_jingli"));
  	ob->set("max_qi",me->query("max_qi"));
  	ob->set("max_jing",me->query("max_jing"));
		ob->set("neili",query("max_neili")*3/2);
		ob->set("jingli",query("max_jingli")*3/2);
		ob->set("eff_jingli",query("max_jingli")*3/2);
		ob->set("qi",query("max_qi"));
		ob->set("eff_qi",query("max_qi"));
		ob->set("jing",query("max_jing")*3/2);
		ob->set("eff_jing",query("max_jing")*3/2);
    ob->set("jiali",100);
    ob->set_skill("wuxing-zhen",200);
    ob->set("combat_exp",me->query("combat_exp"));
    ob->set("fy5_id",me->query("id"));
 		ob->set_skill("literate",ob->query("int")*10); 	 											//full literate
    remove_call_out("do_kill");
    remove_call_out("dest");
    call_out("dest",600,ob);
    call_out("do_kill",2,me);
}
int do_kill(object me)
{
	object ob = this_object();
	if(!me) return 0;
    if(!me->query_temp("quest/huashan/fy5/killer_killed"))
        message_vision(HIY"$N冷笑一声道：不知天高地厚，竟然敢来管"+RANK_D->query_self_rude(ob) +"我，今天就要你的命！\n"NOR,ob);
    else
        message_vision(HIW"$N冲着$n长啸一声：“大胆鼠辈，竟敢坏我等好事，留你不得!\n"NOR,ob,me);
  command("follow "+me->query("id"));
  ob->set_leader(me);
	remove_call_out("checking");
   if(!ob->query("fengyi5_boss"))
       call_out("checking", 2, me, ob);
    else me->set("quest/hsjf/fy5/yanlian","again");
    me->start_busy(2+random(2));
    ob->start_busy(3);
	::do_kill(me);
    return 1;
}

//检查，quest过程不允许死亡
int checking(object me, object ob)
{
	int ret =  ::checking(me,ob);
	if(!ret) return 0;
	remove_call_out("checking");
	call_out("checking", 1, me, ob);
  if(!living(me) && living(ob) && ob->query("jing")>0 && ob->query("jingli")>0 && ob->query("qi")>0  ){
		remove_call_out("checking");
		me->set("qi",100);																		
    log_file("quest/fengyi5", sprintf(HIY"有凤来仪5Quest记录：%s(%s)"HIW"挑战"HIY"第%d个蒙面恶人失败。经验%d。"NOR, me->name(1),me->query("id"), (int)me->query_temp("quest/huashan/fy5/killer_killed")+1,me->query("combat_exp")) );
                me->set("jing",100);
                me->set("jingli",100);
                me->set("quest/hsjf/fy5/exp",me->query("combat_exp"));
                me->set("quest/hsjf/fy5/time",time());
                me->add("quest/hsjf/fy5/kill_killer_fail",1);
                me->set("quest/hsjf/fy5/yanlian","again");
                me->delete_temp("quest/huashan/fy5");
          if(!random(3)) tell_room(environment(ob), HIB"\n"+ob->name()+"哼了一声，转身几个起落就不见了。\n"NOR);
        else tell_room(environment(ob), HIB"\n"+ob->name()+"轻蔑的瞟了"+me->name()+"一眼道：“这种本事就不要再出来丢人现眼了!”\n"NOR);
		destruct(ob);
		return 1;
	}
  if(!me || environment(ob)!= environment(me)||me->query("eff_qi")<me->query("max_qi")/10||me->query("qi")<me->query("max_qi")/15){
		remove_call_out("checking");
		remove_call_out("do_lost");
		call_out("do_lost",0);
		return 1;
	}
   if(!me->is_fighting(ob))  call_out("do_kill",1,me);
}
void do_lost()
{
	object me,ob;
	ob = this_object();
   me = find_player(ob->query("fy5_id"));
	if(!me) return;
    log_file("quest/fengyi5", sprintf(HIY"有凤来仪5Quest记录：%s(%s)"HIW"挑战"HIY"第%d个蒙面恶人失败。经验%d。"NOR, me->name(1),me->query("id"), (int)me->query_temp("quest/huashan/fy5/killer_killed")+1,me->query("combat_exp")) );
    me->set("quest/hsjf/fy5/exp",me->query("combat_exp"));
    me->set("quest/hsjf/fy5/time",time());
    me->add("quest/hsjf/fy5/kill_killer_fail",1);
    me->set("quest/hsjf/fy5/yanlian","again");
    me->delete_temp("quest/huashan/fy5");
        if(!random(3)) tell_room(environment(ob), HIB"\n"+ob->name()+"哼了一声，转身几个起落就不见了。\n"NOR);
        else tell_room(environment(ob), HIB"\n"+ob->name()+"轻蔑的瞟了"+me->name()+"一眼道：“这种本事就不要再出来丢人现眼了!”\n"NOR);
	destruct(ob);
}

void dest(object ob)
{
  if(!ob) return;
  tell_room(environment(ob), HIR+"\n"+ob->name()+"哼了一声，转身几个起落就不见了。\n"NOR);
	destruct(ob);
}

void die()
{
    object killer,ob,newob;
    mapping name;

    name = RNAME_D->get_random_name(random(3));

    ob = this_object();
    if(!objectp(killer = query_temp("last_damage_from"))){
        ::die();
        return;
    }

    if(!killer->query("quest/hsjf/fy5/meet_killers")){
        ::die();
        return;
    }

    if(!killer->query_condition("fy5_killers")&&(int)killer->query_temp("quest/huashan/fy5/killer_killed")>3){
        if(ob->query("fengyi5_boss")){
            tell_object(killer,HIM"你只觉得"+ob->query("name")+"使得华山剑法奇特无比，顿时让你想到了石壁上的剑招。\n"+
            HIG+"突然你觉得如果可以再次揣摩下，或许会有新的发现！\n"NOR);
            killer->delete("quest/hsjf/fy5/meet_killers");
            killer->delete("quest/hsjf/fy5/location");
            killer->set("quest/hsjf/fy5/chuaimo",1);
            killer->set("quest/hsjf/fy5/exp",killer->query("combat_exp"));
            killer->set("quest/hsjf/fy5/time",time());
            killer->set("quest/hsjf/fy5/kill_killer_pass",1);
            killer->set("quest/hsjf/fy5/yanlian","pass");
            killer->delete_temp("quest/huashan/fy5");
            log_file("quest/fengyi5", sprintf(HIG"有凤来仪5Quest记录：%s(%s)"HIW"成功"HIG"挑战蒙面恶人BOSS。经验%d。"NOR, killer->name(1),killer->query("id"),killer->query("combat_exp")) );
            ::die();
            return;
        }
    message_vision(HIW"\n“哈哈哈！”，突然传来一阵冷笑声，“"+RANK_D->query_rude(killer) +"！武功不错啊，可惜就要去见阎王了！”\n"NOR,ob,killer);
    newob = new(__DIR__"fy5_npc");
    newob->set("party","hs");
    newob->set("fengyi5_boss",1);
    newob->set_name(name["name"], name["id"]);
    newob->set_name(newob->query("name"), ({ newob->query("id"),"killer"}));
    newob->move(environment(killer));
    killer->add_temp("quest/huashan/fy5/killer_killed",1);
    log_file("quest/fengyi5", sprintf(HIC"有凤来仪5Quest记录：%s(%s)"HIW"获得"HIC"挑战蒙面恶人BOSS机会。经验%d。"NOR, killer->name(1),killer->query("id"),killer->query("combat_exp")) );
    destruct(ob);
    return;
    }

    message_vision(HIY"\n突然又蹿出一个"HIB"蒙面恶人"HIY"，对$N"HIY"叫道：“哼！你且撤退，让我来教训教训这个"+RANK_D->query_rude(killer) +"！\n"NOR,ob,killer);
    message_vision(HIR"$N"HIR"连道:“兄弟小心，这个"+RANK_D->query_rude(killer) +"身手不错！”，说完就转身几个起落不见了。！\n\n"NOR,ob,killer);
    newob = new(__DIR__"fy5_npc");
    newob->move(environment(killer));
    killer->add_temp("quest/huashan/fy5/killer_killed",1);
    destruct(ob);
    return;
}
