// sohu@xojh
//�������´���
inherit ITEM;
void create()
{
       set_name("�ڹ���Ҫ", ({ "neigong jingyao", "book", "jingyao" }));
       set_weight(250);
       if( clonep() )
	   set_default_object(__FILE__);
       else {
	   set("unit", "��");
	   set("long", "����һ�����ƾɵ�С���ӣ����Ǵ���ʼұ�����ķ���Ҫ����ֻʣ��ǰ��ҳ�������������������ơ�\n");
	   set("value", 500);
	   set("material", "paper");
       set("unique", 1);
       set("treasure", 1);
	   set("skill", ([
		"name":	"force",	 
		"exp_required":	3000, 
        "jing_cost":    10,   
		"difficulty":	20, 
		"max_skill":	50, 
	   ]));
	}
}
