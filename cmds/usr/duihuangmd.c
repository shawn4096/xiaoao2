
inherit F_CLEAN_UP;
#include <ansi.h>

int help(object me);


string check(object me)
{
	string msg;

	if (me->query("gmd_job/gmdscore") < 500)
		msg = HIY"ϵͳ��ʾ��"NOR"��Ǹ�����Ļ��ֲ����Զһ���\n";
	if (me->is_ghost())
		msg = HIY"ϵͳ��ʾ��"NOR"��Ǹ�����״̬���ȶ��������޷��һ���\n";
	return msg;
}


int main(object me, string arg)
{
	string msg;
	int num,jobs;
	if (!me) return 0;
	if (!arg) return help(me);
	if ( stringp(msg = check(me)) )
		return notify_fail(msg);
	if (sscanf(arg, "%d", num) == 1){	
	   if (num<500 ) return notify_fail("���һ�£�500�������޷��һ���\n");
    if (me->query("gmd_job/gmdscore") < num)
			return notify_fail("��Ļ���û����ô�ࡣ\n");
		jobs=num /500;
		me->add("gmd_job/gmdscore",-jobs*500);
		me->add("job_time/Χ��������",jobs);
		write("��ʹ����"+jobs*500+"����������ֶһ���"+jobs+"��Χ������������\n");
		write("�����й���������"+me->query("gmd_job/gmdscore")+"�㡣\n");
		me->save();
	    log_file("static/gmdscore",
		me->query("name")+"("+capitalize(geteuid(me))+")"
		+"�һ�"+num+"�㣬����Χ��������job����"+jobs+"�Ρ�\n",
		me,
		({ me })
	);
		
		return 1;
	}
	return help(me);
	
}

int help(object me)
{
	write("	��ָ�����������»��ֶһ�Ϊ�´�����job������\n");
    write("	500���ֿɶһ�1���´����¡�\n\n");
	write("	��Ŀǰӵ�л���"+me->query("gmd_job/gmdscore")+"�㡣\n\n");
	write("	�����ֲ���"+500+"���ܶһ���\n");
	write("	ָ���ʽ��\n");
	write("	duihuangmd 500\n");	
	write("	ע�⣬��Ϊ��ȡ500������������ʹ����501��������ֵ��Ҳֻ��۳�500�֡�\n");
	return 1;
}