inherit ITEM;

void create()
{
        set_name("����ѩɽ�Ʒ�(��)", ({ "shentuo zhangfa", "zhangfa", "book" }));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long",
                        "����һ������<<����ѩɽ�Ʒ�>>���鼮������ŷ����������Ϭ���쳣��\n");
                set("value", 500);
                set("material", "paper");
                set("unique", 1);
			//	set("no_drop", "��ô���������ؼ�����ɲ������ⶪ����\n");
              //  set("no_get", "�������������˵ı�������˯����Ҫ����ͷ�棬���޷���ȡ��\n");
                set("no_give", "��ô���������ؼ�����ɲ���������ˣ�\n");

                set("treasure", 1);
                set("skill", ([
                        "name": "shentuo-zhang",      // name of the skill
                        "exp_required": 500,  // minimum combat experience required
                        "jing_cost":    25,     // jing cost every time study this
                        "difficulty":   30,     // the base int to learn this skill
						"min_skill":    100,
                        "max_skill":    200,      // the maximum level you can learn
                ]) );
        }
}
