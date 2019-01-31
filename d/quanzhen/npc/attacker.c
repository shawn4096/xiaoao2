#include <ansi.h>
inherit NPC;
int do_copy(object me);

string *sword_skill = ({ 
"taiji-jian","damo-jian","fumo-jian","jinshe-jianfa","qingmang-jian","yuxiao-jian",
"yunu-jianfa","songshan-jian","murong-jianfa","huashan-jianfa", "duanjia-jianfa",
"huifeng-jian","liangyi-jian","quanzhen-jianfa" }); 

string *blade_skill = ({ 
"cibei-dao","fanliangyi-dao","liuhe-daofa","murong-daofa","yanxing-daofa","ruyi-dao","wenjia-daofa", "ranmu-daofa", 
"shandian-daofa","xiuluo-dao","xuanxu-daofa", "yanxing-daofa",}); 

string *staff_skill = ({ "wuchang-zhang","fengmo-zhang","tianshan-zhang","xinyuegong" }); 

string *club_skill = ({ "weituo-chu","zui-gun","weituo-gun","xinyuegong" }); 

string *whip_skill = ({ "piaomiao-bianfa","qingxu-bian" }); 

string *dodge_skill = ({ 
"shuishangpiao","suibo-zhuliu","yanling-shenfa","caoshang-fei","tianlong-xiang",
"yunu-shenfa","zhaixingshu","xiaoyaoyou","zhongyuefeng","huashan-shenfa","tiyunzong" }); 

string *weapon_list = ({ "chui","sword","blade","whip","gun","sword","gangzhang","blade" }); 

string *first_name = ({ "蒙面大汉","黑衣人","神秘人","黑道人物","山贼","淫贼","草贼","草寇"}); 

void create()
{
        string s_sword,s_blade,s_club,s_whip,s_staff,s_dodge, weapon, name;        
        name = first_name[random(sizeof(first_name))];
        s_sword = sword_skill[random(sizeof(sword_skill))];
        s_blade = blade_skill[random(sizeof(blade_skill))];
        s_club  = club_skill[random(sizeof(club_skill))];
        s_whip  = whip_skill[random(sizeof(whip_skill))];
        s_staff = staff_skill[random(sizeof(staff_skill))];
        s_dodge = dodge_skill[random(sizeof(dodge_skill))];
        weapon = weapon_list[random(sizeof(weapon_list))];

        set_name(name, ({ "attacker"}));
        set("gender", "男性");
        set("age", 20 + random(40));
        set("long", "这家伙一付凶神恶煞的模样，时不时发出邪恶的阴笑。\n");
        set("combat_exp", 20000);
//      set("attitude", "aggressive");
        set("attitude", "peaceful");
        set("str", 50);
        set("int", 22);
        set("con", 24);
        set("dex", 30);
        set("max_qi", 34000);
        set("max_jing", 6000);
        set("neili", 26000);
        set("max_neili", 26000);
        set("jiali", 210);
        set("location",1);
        set_skill("taizu-quan", 530);
        set_skill("xinyuegong", 530);
        set_skill("cuff", 530);
        set_skill("force", 530);
        set_skill("yinyun-ziqi", 530);
        set_skill("sword", 530);
        set_skill("parry", 530);
        set_skill("dodge", 530);
        set_skill("blade", 530);
        set_skill("hammer", 530);
        set_skill("club", 530);
        set_skill("staff", 530);
        set_skill("whip", 530);
        set_skill(s_sword, 530);
        set_skill(s_blade, 530);
        set_skill(s_club, 530);
        set_skill(s_whip, 530);
        set_skill(s_staff, 530);
        set_skill(s_dodge, 530);
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

void greeting(object ob)
{
        if (!ob || !present(ob, environment())) destruct(this_object());

        if ( ob->query_temp("qz/shouwei") && this_object()->query("target")==ob->query("id"))
      {
              remove_call_out("kill_ob");
              call_out("kill_ob", 0, ob);
      }   
}

/*               
void unconcious()
{    
        tell_room(environment(this_object()), HIR"\n只见"+this_object()->query("name")+"转身几个起落就不见了。\n"NOR, ({this_object()}));
        destruct(this_object());        
}*/
void die()
{
	object me,ob=this_object();
	object fbroom;
      me=ob->query_temp("last_damage_from");
  
	if(objectp(me)) 
	{	
	me->set_temp("qz/shouwei/finish",1);
	me->delete_temp("qz/shouwei/askyin");	   
	}
		/*
	{
      tell_object(me,HIR"\n这"+ob->name()+"眼见就要丧命，大喊道，后面还有兄弟回来，走着瞧。\n"NOR);
	  tell_room(environment(me),HIC"\n只见，"+ob->name()+"似乎重伤在身，向"+me->query("name")+"似乎哀求着什么。\n"NOR, ({ me }));
	  
	  me->add_temp("qz/shouwei/killer",1);
      if (me->query_temp("qz/shouwei/killer")==3)
      {
        tell_object(me,HIY"\n这"+ob->name()+"眼见就要丧命，突然开口向你求饶，告诉你说这是一个阴谋。\n"NOR);
		tell_object(me,HIY"\n按"+ob->name()+"所说，这次的阴谋完全是受一个叫霍都的所指示，\n"
                       "你心中了然，然后决定回去跟师傅说一声，及早做好规划和谋算。\n"NOR);

		tell_object(me,HIC"\n你听完"+ob->name()+"之后，嘿嘿两声，还是手下不留情面。\n"NOR);
		tell_room(environment(me),HIC"\n"+ob->name()+"说完很多之后，然而不知为何，似乎气血一震，好像失去了什么似的，慢慢萎靡倒地。\n"NOR, ({ me }));
		me->delete_temp("qz/askyin");
		me->delete_temp("qz/guard");
		message_vision(HIG"\n\n"+me->query("name")+"，你已经杀了三批来此骚扰龙姑娘的淫贼了，估计差不多，该回去跟师傅交差了。\n"NOR, me);
	  }
   } */
	::die();
}


int do_copy(object me)
{
        object ob, weapon;
        string my_id, type, type1;
        int i;
        ob = this_object();

        if(!me) destruct(ob);
        my_id = me->query("id");
        weapon = ob->query_temp("weapon"); 
          
        i = me->query_skill("dodge",1) - (10 + random(40));
        if(i < 30) i = 30;
        ob->set("combat_exp", me->query("combat_exp")/5*4);
        if(weapon) {
           type = weapon->query("skill_type");
           type1 = ob->query_skill_mapped(type);
           ob->set_skill(type, i);
           ob->set_skill(type1, i);
        }
        ob->set_skill("force", i);
        ob->set_skill("cuff", i);
        ob->set_skill("dodge", i);
        ob->set_skill("parry", i);
        ob->set_skill(ob->query_skill_mapped("dodge"), i);
        ob->set_skill("xinyuegong", i);  
        ob->set_skill("yinyun-ziqi", i);     
        ob->set_skill("taizu-quan", i); 
        ob->set("max_qi", me->query("max_qi")/3*2); 
        ob->set("max_jing", me->query("max_jing")/3*2); 
        ob->set("max_neili", me->query("max_neili")/3*2);
        ob->set("jiali", ob->query_skill("force",1)/3);
        ob->reincarnate(); 
        
		ob->set("eff_jing", me->query("eff_jing")/3*2);
        ob->set("jingli", me->query("jingli")/3*2);
        ob->set("neili", me->query("max_neili")/3*2);
        ob->set("qi", me->query("max_qi")/3*2);
        command("stare " + me->query("id"));
        remove_call_out("checking");
        
		call_out("checking", 1, me, ob);
        
		ob->set("victim", me->query("id"));
        return 1;
}

int checking(object me, object ob)
{
        if(!ob) return 0;
        
		if(!me || environment(me)!= environment(ob)) destruct(ob);
        
		if(ob->is_fighting()){
          call_out("checking", 1, me, ob);
          return 1;
        }
        else if(!ob->is_killing(me->query("id")) ) {
          ob->kill_ob(me);
          call_out("checking", 1, me, ob);
          return 1;
        }
        else destruct(ob);
        return 1;
}

int accept_fight(object victim)
{
        if (this_object()->query("target")!=victim->query("id")) 
        {
			this_object()->remove_all_enemy();

			write("那不是你的菜，瞎折腾什么？\n");
			return 1;
        }
		command("say 你这是找死！");
        kill_ob(victim);
        return 1;
}
