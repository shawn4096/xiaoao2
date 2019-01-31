// unwield.c

inherit F_FROZEN;
inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	string str;

	if( !arg ) return notify_fail("��Ҫ�ѵ�ʲô��\n");

	if (userp(me) && me->is_busy())
		return notify_fail("����æ���ء�\n");

	if (userp(me) && me->is_exert()) 
		return notify_fail("������ʹ��"+me->query_exert()+"��\n");

	if (userp(me) && me->is_perform()) 
		return notify_fail("������ʹ��"+me->query_perform()+"��\n");

	if( !objectp(ob = present(arg, me)) )
		return notify_fail("������û������������\n");

	if( (string)ob->query("equipped")!="wielded" )
		return notify_fail("�㲢û��װ������������Ϊ������\n");

	if( ob->unequip() ) {
		if( userp(me) && me->is_fighting()) me->start_busy(1);
		if( !stringp(str = ob->query("unwield_msg")) )
			str = "$N�������е�$n��\n";
		message_vision(str, me, ob);
		return 1;
	} else
		return 0;
}

int help(object me)
{
  write(@HELP
ָ���ʽ : unwield <��Ʒ��>
 
���ָ������������е�������
 
HELP
    );
    return 1;
}