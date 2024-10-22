
#include <ansi.h>;
inherit NPC;
//inherit F_MASTER;
int do_cry();
void dest_ob(object ob,object me);
void create()
{
        set_name("洪七公", ({"hong qigong", "hong", "qigong"}));
        set("nickname", "九指神丐");
        set("gender", "男性");
        set("age", 75);
        set("long", 
"他一张长方脸，颌下微须，粗手大脚，身上衣服东一块西一块的打满了补丁，
却洗得干干净净，背上负着个朱红漆的大葫芦。\n");
        set("attitude", "peaceful");
        
        set("str", 35);
        set("int", 24);
        set("con", 30);
        set("dex", 30);

        set("rank", 10);

        set("max_qi", 4000);
        set("max_jing", 3000);
        set("neili", 5500);
        set("max_neili", 5500);
        set("jiali", 300);
        
        set("combat_exp", 3600000);
        set("score", 200000);
        set("death_times",180);

        set_skill("force", 400);             // 基本内功
        set_skill("huntian-qigong", 400);    // 混天气功
        set_skill("strike", 400);            // 基本掌法
        set_skill("xianglong-zhang", 400);   // 降龙十八掌
        set_skill("hand", 360);              // 基本手法
        set_skill("dodge", 400);             // 基本躲闪
        set_skill("xiaoyaoyou", 400);        // 逍遥游
        set_skill("parry", 400);             // 基本招架
        set_skill("stick", 400);             // 基本棍杖
        set_skill("dagou-bang", 400);        // 打狗棒法
        set_skill("begging", 200);           // 叫化绝活
        set_skill("checking", 200);          // 道听途说

        map_skill("force", "huntian-qigong");
        map_skill("strike","xianglong-zhang");
        map_skill("hand",  "shexing-diaoshou");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("parry", "dagou-bang");
        map_skill("stick", "dagou-bang");
        
        prepare_skill("strike", "xianglong-zhang");

        create_family("丐帮", 17, "帮主");
        setup();
        
            carry_object(ARMOR_D("bainayi"))->wear();
            carry_object(ARMOR_D("shoes"))->wear();

}

void init(){
        set_heart_beat(1);
        add_action("do_cry","cry");
}

void dest_ob(object ob,object me)
{
        object hong;
		object fbroom;
		fbroom= new("/u/anger/jueding5fb");
		me->set_temp("fbroom",fbroom);
        me->move(fbroom);
        hong = new("/d/huashan/hamasuperquest/hong2");
        hong->move(fbroom);
        destruct(ob);

}

int do_cry()
{
        object me=this_player();
        object ob = this_object();
        object room,*inv;
        int i,j;	
		

        if ((me->query("oyf/hamagong") ==2) || (me->query_temp("wugou/askguo"))) 
        {       
        
                command("haha");
                command("say 小娃儿，有什么伤心事快说给你公公听听！\n");
                tell_object(me,HIM"你觉得身体一轻，洪七公已拉着你跃上了华山绝顶！\n"NOR);
                dest_ob(ob,me);
				return 1;                
        }
		else
		{
			 tell_object(me,HIM"你是不是有毛病？\n"NOR);
			 return 1;
		}
        
}

