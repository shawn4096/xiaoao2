// user list by renlai ��Ӳ鿴quest����

inherit F_CLEAN_UP;

int main(string str)
{
        object *ob,temp;
        int i;
		string vip="��ͨ�û�";
		string jiebai="���δ��";	
        int print=0;		

		
	string a="������������";
	string b="����";
	int ret=0;
	
	ret=strsrch(a,b);
	write("***"+ret+"***\n");
	ob = filter_array(objects(), (: userp :));
	for(i=0; i<sizeof(ob); i++)
	{	    	temp=ob[i];
	    if (temp->query("m-card-vip")) vip="�¿�";
		else if (temp->query("y-card-vip")) vip="�꿨";
		else if (temp->query("buyvip")) vip="����";
		if (temp->query("quest/jiebai/pass")) { 
		jiebai="*�⿪���*"; 
		print=1;
		}
		if (temp->query("double_attack")) jiebai="*�⿪����*";
        if (print==1) write(sprintf("%10s : %40O%s\n", temp->query("id"),vip,jiebai,temp,
		interactive(temp)?"":" �����У�"));
		vip="��ͨ�û�";
		jiebai="���δ��";
		print=0;
	}
        return 1;
	
}

int help(object me)
{
write(@HELP
ָ���ʽ : ulist

������������ҵ�/obj/user number ��ʾ������
HELP
    );
    return 1;
}
