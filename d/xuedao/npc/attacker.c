#include <ansi.h>
inherit NPC;
int do_copy(object me);
//#include "attacker.h"

string *sword_skill = ({ 
"taiji-jian","damo-jian","fumo-jian","jinshe-jianfa","qingmang-jian","yuxiao-jian",
"yunu-jianfa","songshan-jian","murong-jianfa","huashan-jianfa", "duanjia-jianfa",
"huifeng-jian","liangyi-jian","quanzhen-jianfa" }); 

string *blade_skill = ({ 
"cibei-dao","fanliangyi-dao","liuhe-daofa","murong-daofa","qingmang-jian","wenjia-daofa", 
"shandian-daofa","xiuluo-dao","xuanxu-daofa", "yanxing-daofa",}); 

string *staff_skill = ({ "wuchang-zhang","fengmo-zhang","tianshan-zhang","xinyuegong" }); 

string *club_skill = ({ "weituo-chu","zui-gun","weituo-gun","xinyuegong" }); 

string *whip_skill = ({ "piaomiao-bianfa","qingxu-bian" }); 
string *spear_skill = ({ "zhong-qiang","yangjia-qiang" ,"bawang-qiang"}); 

string *dodge_skill = ({ 
"shuishangpiao","suibo-zhuliu","yanling-shenfa","yufeng-xiang","tianlong-xiang",
"yunu-shenfa","zhaixingshu","xiaoyaoyou","zhongyuefeng","huashan-shenfa","tiyunzong" }); 

string *weapon_list = ({ "chui","spear","sword","blade","whip","gun","sword","gangzhang","blade" }); 

string *first_name = ({ "白衣侠客","白衣人","岭南双侠人物","正道人物","江南四侠弟子","落花流水弟子"}); 

void create()
{
        string s_sword,s_blade,s_club,s_whip,s_staff,s_dodge,s_spear, weapon, name;        
        name = first_name[random(sizeof(first_name))];
        s_sword = sword_skill[random(sizeof(sword_skill))];
        s_blade = blade_skill[random(sizeof(blade_skill))];
        s_club  = club_skill[random(sizeof(club_skill))];
        s_whip  = whip_skill[random(sizeof(whip_skill))];
        s_staff = staff_skill[random(sizeof(staff_skill))];
        s_dodge = dodge_skill[random(sizeof(dodge_skill))];
		s_spear = spear_skill[random(sizeof(spear_skill))];

        weapon = weapon_list[random(sizeof(weapon_list))];

        set_name(name, ({ "attacker"}));
        set("gender", "男性");
        set("age", 20 + random(40));
        set("long", "一袭白衣，满身正气，一看就是行走江湖的大侠。\n");
        set("combat_exp", 20000);
        set("attitude", "aggressive");
        //set("attitude", "peaceful");
        set("str", 50);
        set("int", 22);
        set("con", 24);
        set("dex", 30);
        set("max_qi", 40000);
        set("max_jing", 4000);
        set("neili", 26000);
        set("max_neili", 26000);
        set("jiali", 200);
        set("location",1);
        set_skill("taizu-quan", 30);
        set_skill("xinyuegong", 30);
        set_skill("cuff", 30);
        set_skill("force", 30);
        set_skill("yinyun-ziqi", 30);
        set_skill("sword", 30);
        set_skill("parry", 30);
        set_skill("dodge", 30);
        set_skill("blade", 30);
        set_skill("hammer", 30);
        set_skill("club", 30);
		set_skill("spear", 30);
        set_skill("staff", 30);
        set_skill("whip", 30);
        set_skill(s_sword, 30);
		//set_skill(s_spear, 30);
        set_skill(s_blade, 30);
        set_skill(s_club, 30);
        set_skill(s_whip, 30);
        set_skill(s_staff, 30);
        set_skill(s_dodge, 30);
        map_skill("force", "yinyun-ziqi");
        map_skill("sword", s_sword);
        map_skill("dodge", s_dodge);
        map_skill("parry", "taizu-quan");
        map_skill("hammer", "xinyuegong");
        map_skill("blade", s_blade);
        map_skill("club", s_club);
        map_skill("whip", s_whip);
        map_skill("staff", s_staff);
        map_skill("cuff", "taizu-quan");
        prepare_skill("cuff", "taizu-quan");         
        setup();
        carry_object(BINGQI_D(weapon))->wield();
        carry_object(ARMOR_D("yexing-yi"))->wear();
}       

void init()
{       
       object ob;

        ::init();
        if (base_name(environment()) != query("startroom")) return;
        if( interactive(ob = this_player()) && visible(ob) ) 
          {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
          }
}
int do_kill(object ob)
{
	object me = this_object();
	if(!ob) return 0;
	//增加判断是否自己的npc
	if (me->query("owner")!=ob->query("id"))
		return notify_fail("他和你无冤无仇，你干嘛要乱杀无辜？\n");
	kill_ob(ob);
}

void greeting(object ob)
{
        if (!ob || !present(ob, environment())) return;
		//邪门歪道，人人得而诛之，全杀，不针对某人
        if ( ob->query_temp("xdzj_job") && this_object()->query("owner")==ob->query("id") )
      {
              remove_call_out("kill_ob");
              call_out("kill_ob", 0, ob);
      }   
}

                
void unconcious()
{    
        tell_room(environment(this_object()), HIR"\n只见"+this_object()->query("name")+"转身几个起落就不见了。\n"NOR, ({this_object()}));
        destruct(this_object());        
}


int checking(object me, object ob)
{
        if(!ob) return 0;
        if(!me || environment(me)!= environment(ob)) ob->unconcious();
        if(ob->is_fighting()){
          call_out("checking", 1, me, ob);
          return 1;
        }
        else if(!ob->is_killing(me->query("id")) ) {
          ob->kill_ob(me);
          call_out("checking", 1, me, ob);
          return 1;
        }
        else ob->unconcious();
        return 1;
}

int accept_fight(object victim)
{
        command("say 淫贼，如此作恶多端，纳命来吧！");
        kill_ob(victim);
        return 1;
}
