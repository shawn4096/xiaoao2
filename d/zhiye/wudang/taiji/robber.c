inherit NPC;
inherit F_UNIQUE;
inherit F_SAVE;
#include <ansi.h>

int do_kill(object me);

string *sword_skill = ({ 
"taiji-jian","damo-jian","fumo-jian","jinshe-jianfa","qingmang-jianfa","yuxiao-jian",
"yunu-jianfa","songshan-jian","murong-jianfa","huashan-jianfa", "duanjia-jianfa",
"huifeng-jian","liangyi-jian","quanzhen-jianfa" }); 

string *blade_skill = ({ 
"cibei-dao","fanliangyi-dao","liuhe-daofa","murong-daofa","qingmang-jianfa","wenjia-daofa", 
"shandian-daofa","xiuluo-dao","xuanxu-daofa", "yanxing-daofa",}); 

string *staff_skill = ({ "wuchang-zhang","fengmo-zhang","tianshan-zhang","xinyuegong" }); 

string *club_skill = ({ "weituo-chu","zui-gun","weituo-gun","xinyuegong" }); 

string *whip_skill = ({ "piaomiao-bianfa","qingxu-bian" }); 

string *dodge_skill = ({ 
"shuishangpiao","suibo-zhuliu","yanling-shenfa","yufeng-xiang","tianlong-xiang",
"yunu-shenfa","zhaixingshu","xiaoyaoyou","zhongyuefeng","huashan-shenfa","tiyunzong" }); 

string *weapon_list = ({ "chui","sword","blade","whip","gun","sword","gangzhang","blade" }); 

string *first_name = ({ "草寇","寨主","恶霸","流氓","山贼","土匪","飞贼","地痞","无赖","盗贼"}); 

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

        set_name(name, ({ "robber"}));
        set("gender", "男性");
        set("age", 20 + random(40));
        set("long", "这家伙一付凶神恶煞的模样，时不时发出邪恶的阴笑。\n");
        set("combat_exp", 800000);
//        set("meitude", "aggressive");
        set("meitude", "peaceful");
        set("str", 20);
        set("dex", 20);
        set("int", 20);
        set("con", 20);
        set("max_qi", 20000);
        set("max_jing", 20000);
        set("max_neili", 5000);
        set("neili", 5000);
        set_skill("huagu-mianzhang", 500);
        set_skill("strike", 500);
        set_skill("xinyuegong", 500);
        set_skill("yinyun-ziqi", 200);
        set_skill("sword", 500);
        set_skill("dodge", 500);
        set_skill("cuff", 500);
        set_skill("force", 500);
        set_skill("parry", 500);
        set_skill("blade", 500);
        set_skill("hammer", 500);
        set_skill("club", 500);
        set_skill("staff", 500);
        set_skill("whip", 500);
        set_skill(s_sword, 500);
        set_skill(s_blade, 500);
        set_skill(s_club, 500);
        set_skill(s_whip, 500);
        set_skill(s_staff, 500);
        set_skill(s_dodge, 500);
        map_skill("force", "yinyun-ziqi");
        map_skill("sword", s_sword);
        map_skill("dodge", s_dodge);
        map_skill("parry", "taizuquan");
        map_skill("hammer", "xinyuegong");
        map_skill("blade", s_blade);
        map_skill("club", s_club);
        map_skill("whip", s_whip);
        map_skill("staff", s_staff);
        map_skill("strike", "huagu-mianzhang");
        prepare_skill("strike", "huagu-mianzhang");
        prepare_skill("cuff", "taizuquan");         
        setup();
        carry_object(BINGQI_D(weapon))->wield();
        carry_object(ARMOR_D("yexing-yi"))->wear();
        add_money("silver", random(10));
        set("chat_chance", 3);
        set("chat_msg", ({
                (: random_move :)
        }) );
        this_object()->start_call_out( (: call_other, this_object(), "dest", this_object() :), 600);

}       
void init()
{
        object ob;
        
        ::init();
        
        if( interactive(ob = this_player()) )
        {
                remove_call_out("greeting");
                call_out("greeting", 0, ob);
        }
}

void greeting(object ob)
{
        object me = this_object();
      
        if (ob->query("mwd/step2"))
        {
			
			message_vision(HIR""+me->name()+"对着$N发出一阵阴笑，说道：既然被你这个" + RANK_D->query_rude(ob)+ "撞见了，那也就只能算你命短了！\n\n"NOR,ob);
                        ob->start_busy(1+random(2));
                        remove_call_out("checking");
                        call_out("checking", 1, me, ob);
                        //remove_call_out("dest");
                       // call_out("dest",200);
                        remove_call_out("do_kill");
                        call_out("do_kill", 0, ob);
                    
        }
        return;
}



int do_kill(object ob)
{
        mapping skills;
        string *sk;
        object me; 
        int lv,exp,i,b_exp;
        me=this_object();
        lv=(int)ob->query("max_pot");
        lv = lv-100;
        exp = ob->query("combat_exp");
        b_exp=300000;
        
        if (exp<300000)
         {
            me->set("combat_exp",exp);
	    lv=lv*(random(3)+6)/10;
	 } else {
	me->set("combat_exp",(exp+random(20000*(exp/b_exp))));
        lv=lv*(random(3)+8)/10;
        }     
        me->set("qi",(int)ob->query("max_qi"));
        me->set("max_qi", (int)ob->query("max_qi"));
        me->set("eff_qi", (int)ob->query("max_qi"));
        me->set("jing",(int)ob->query("max_jing"));
        me->set("max_jing",(int)ob->query("max_jing"));
        me->set("eff_jing",(int)ob->query("max_jing"));
        me->set("neili",(int)ob->query("max_neili")*4/5);
        me->set("max_neili",(int)ob->query("max_neili") );
        me->set("jingli",(int)ob->query("max_jingli"));
        me->set("eff_jingli",(int)ob->query("max_jingli"));
        
        skills = me->query_skills();
        if (mapp(skills)) 
          {
                sk = keys(skills);
                for (i=0;i<sizeof(sk);i++)
                        skills[sk[i]] = lv;
          }
        me->kill_ob(ob);
        remove_call_out("checking");
        call_out("checking", 1, me, ob);
      
}
