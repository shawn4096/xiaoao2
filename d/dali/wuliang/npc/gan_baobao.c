// NPC :gan_baobao.c �ʱ��� 
// By River 98/12
#include <ansi.h>

inherit NPC;
string ask_duan();
int yun_come(object me);
int zhong_come(object me);

void create()
{
        set_name("�ʱ���", ({ "gan baobao", "gan", "baobao"}));
        set("title","��ٹȹ�������");
        set("nickname",HIC"��ҹ��"NOR);        
        set("gender", "Ů��" );
        set("age", 36);
        set("str", 17);
        set("con", 23);
        set("dex", 26);
        set("int", 25);
        set("per", 25);
   		set("attitude", "friendly");

        set("max_qi", 15000);
        set("max_jing", 8000);
        set("eff_jingli", 8000);
        set("neili", 8000);
		set("qi", 15000);	
        set("max_neili", 8000);      
        set("unique", 1);
        
        set("long","�⸾��ԼĪ��ʮ������������ͣ���ɫ���㣬üĿ����ϡ�������������ơ�\n");
        set("combat_exp", 4200000);
        set("shen", 800); 

        set_skill("parry", 380);
        set_skill("dodge", 380);
        set_skill("force", 380);
        set_skill("strike", 380);
        set_skill("qiantian-yiyang", 380);        
        set_skill("tianlong-xiang", 380);
        set_skill("zhongjia-zhang", 380);
        map_skill("dodge", "tianlong-xiang");
        map_skill("parry", "zhongjia-zhang");
        map_skill("strike", "zhongjia-zhang");
        map_skill("force", "qiantian-yiyang");
        prepare_skill("strike","zhongjia-zhang");

        set("inquiry", ([            
            "������" : (: ask_duan :),
        ]));

        setup();
        carry_object(__DIR__"obj/lvshan")->wear();
}

string ask_duan()
{
		object me=this_player();
		if (!me->query_temp("yyzhi/helpgbb")) return "�ߣ�����������������������\n";
		
		command("blush ");
		command("blush ");
		command("say �㵽����˭��Ϊ�θ��������� ");
		command("say ����һλ��ү������ô������ʶ����");
		command("say ���ϴ����˰ɣ� ");
		command("say ������ٹȹ������ˣ��������Ҵ�����Ϊ��������");
		command("say �������������ҡ� ");
		command("say �㲻Ҫ���ҵ���ǰ�ᵽ�������֡�");
		command("say �㿴�������ô�� ");
		command("say ���Ǹ������ĺ��ӣ�");
		command("say ��������ٹȹ���������֪���ģ������ӡ� ");
		command("say ��ٹȹ�������������ɷ�");
		command("say ��ʲô�¸Ͻ�˵�������Һ����ˣ� ");
		command("say .........��");
		command("say .........��");
		command("say .........��");
		message_vision(HIY"\n\n\n\n������ʱ��Ľ��ź���߶���ʱ�������ȷ��$N�Ƕ������������������ˡ�\n"NOR,me);

		message_vision(HIY"\n\n\n\n\��ʱ��Ҳ���Ʋ�ס�Լ����������������������\n"NOR,me);
		message_vision(HIY"\n\n\n\n\������������������\n"NOR,me);
		message_vision(HIY"\n\n\n\n\���ʱ���Ժ󣬸ʱ��������ȶ���������ʼ������˵���µ���������ȥ����\n"NOR,me);
		if (me->query_temp("yyzhi/helpgbb"))
		{		
			me->set_temp("yyzhi/askgan",1);
			message_vision(HIC"\n\n\��֪����ʱ�������ص��Լ��ഺ����������ֳ�������������ɡ�����\n"NOR,me);
			call_out("zhong",2+random(3),me);
			return "��̾һ�����ƺ�����������£����ƺ����в���\n";
		}
		return "";

}

int zhong(object me)
{
	message_vision(HIR"����������һ���ֱ���������������˭��˭��������굽�����ŵķ�����ȥ�ˣ���\n"NOR,me);
	command("say �������������ɷ���Ƕ��ɣ�һ������ˣ����鷳�ɾʹ���!\n");
	command("blush ");

	message_vision(HIC"$N˵�������ʷ��˲�Ҫ���£���ү����������"HIR"(baohu �ʱ���)"HIC"��ģ�������\n"NOR,me);

}