// NPC xie.c лѷ
// Modify By River@sj 99.06
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_me();
string ask_dao();
string ask_boat();
void create()
{
        object ob;
        set_name("лѷ",({"xie xun","xie","xun"}));
        set("title","���̻��̷���");
        set("nickname",HIY"��ëʨ��"NOR);
        set("long", "���������̵��Ĵ󻤷�֮һ�Ľ�ëʨ����\n"+
                    "����Ŀ�ΰ�쳣����ͷ��ɢ����ͷ����˫Ŀ��Ϲ��\n"+
                    "������ǰһվ���������ݣ���������һ�㡣\n");
        set("age", 56);
        set("attitude", "peaceful");
        set("shen", -13000);
        set("str", 30);
        set("per", 16);
        set("int", 29);
        set("con", 35);
        set("dex", 27);        
        set("max_qi", 45000);
        set("max_jing", 12000);
        set("eff_jingli", 12000);
        set("jiali", 200);
        set("combat_exp", 7500000);
        set("unique", 1);

        set_skill("cuff",451); 
        set_skill("dodge",400);
        set_skill("force", 400);
        set_skill("blade",400);
        set_skill("literate",210);
        set_skill("piaoyi-shenfa", 400);
        set_skill("qishang-quan",451);
        set_skill("hunyuan-yiqi", 400);
        set_skill("parry", 400);
        set_skill("lieyan-dao",460);        
        map_skill("force", "hunyuan-yiqi");
        map_skill("dodge", "piaoyi-shenfa");
        map_skill("cuff", "qishang-quan");
        map_skill("parry", "qishang-quan");
        map_skill("blade", "lieyan-dao");
        prepare_skill("cuff","qishang-quan");
        
        set("chat_chance_combat", 20);
        set("chat_msg_combat", ({
                (: perform_action, "cuff.duanhun" :),
					                (: perform_action, "blade.lieyan" :),

                (: exert_function, "shenghuo" :),
		}));

     

        create_family("����", 36, "����");
        setup();
        if (clonep()) {
                ob = unew(BINGQI_D("tulong-dao"));             
                if (ob){
                    ob->move(this_object());
                    ob->wield();
                    }
                carry_object(ARMOR_D("xiongpi"))->wear();
        }  
}
