// lao-qiao.c ������

inherit NPC;

void create()
{
	set_name("������", ({ "lao qiao", "qiao" }));
	set("gender", "����");
	set("age", 55 );
	set("long",
		"����һλ���ް߰׵����ˣ���һϮ�಼�·���������Ըߣ�\n"
		"���ǽ����ú������Ƿ塱�ĸ��ס�\n"
	);
	set_skill("unarmed", 20);
	set_skill("dodge", 20);
	set("qi", 400);
	set("max_qi", 400);
	set("eff_qi", 400);
	set("jing", 300);
	set("max_jing", 300);

	setup();

}
	
