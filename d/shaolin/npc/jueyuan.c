// jueyuan.c ��Զ��ʦ
// cre by sohu@xojh
#include <ansi.h>

inherit NPC;
void create()
{
	set_name("��Զ����", ({
		"jueyuan dashi",
		"jueyuan",
		"dashi",
	}));
	set("long",
		"����ɮ��ʱ��ֻ������������������ȫ���ţ����ǹ�ͷɮ������Ȼ����λ�����๫��\n"
		+"������ȣ���ҩʦ�����������طŵ���ɽ�������� �������ֶ������ֽ������õĳ�͢������\n"
		+"���Զ��ʮ�����ҵ���ͣ� �����Ǹ���ʫ�����Ի���ٲȻ����Ȼ���ֹֻ�㣬���ѵ�����\n"
		+"������һλ��ѧ���塢�������ҡ�\n"
	);
	set("title",HIC"�ؾ�����"NOR);

	set("gender", "����");
	set("attitude", "peaceful");
	set("class", "bonze");

	set("chat_msg",({

	//(: this_object(), "my_move" :),
	"��Զ����������⼸��Ҳ��֣��ؾ���Ȼ����������͵���������鶼͵��\n",

	}));

	set("age", 55);
	set("shen_type", 1);
	set("str", 30);
	set("int", 20);
	set("con", 30);
	set("dex", 20);
	set("max_qi", 63000);
	set("max_jing", 8150);
	set("neili", 50100);
	set("max_neili", 50100);
	set("combat_exp", 15000000);
	set("score", 200);
	set("chat_chance", 20);

	set_skill("force", 550);
	set_skill("dodge", 550);
	set_skill("cuff", 550);
	set_skill("parry", 550);
	set_skill("jiuyang-shengong",550);
	set_skill("shaolin-shenfa",550);
	set_skill("luohan-quan",550);
	map_skill("force","jiuyang-shengong");
	map_skill("cuff","luohan-quan");
	map_skill("parry","luohan-quan");
	map_skill("dodge","huashan-shenfa");
	prepare_skill("cuff","luohan-quan");
	setup();

}

