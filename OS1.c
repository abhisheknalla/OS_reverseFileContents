#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<sys/stat.h>
#include<unistd.h>

int main(int argc, char* argv[])
{

	int source, dest, n;
	char buf;
	size_t filesize;
	int i;

	if (argc != 2) {
		write(1,"usage ./a.out <source> <dest>",29);
		exit(-1);
	}
	if ((source = open(argv[1], O_RDONLY)) < 0) { 
		write(1,"cant open source",16);
		exit(-1);
	}

	mkdir("Assignment",0700);

	if ((dest = creat("Assignment/dest.txt", 0600)) < 0) { 
		write(1,"cant create  dest",17);
		exit(-1);
	}
	int j=0;
	filesize = lseek(source, (off_t) 0, SEEK_END); 
	int resize=filesize;
	if(filesize>100000)
	{
		while(filesize>=1000000)
		{ 
			lseek(source,(off_t)filesize-1000000, SEEK_SET);
			char buff[1000000];
			n = read(source,buff,1000000);
			for(i=99999;i>=0;i--)
			{
				if(buff[i]>64 && buff[i]<91)
					buff[i]+=32;

				else if(buff[i]>96 && buff[i]<123)
					buff[i]-=32;
			}
			if(n!=1000000)
			{
				char a[]="cant read 1000000 byte";
				write(1,"cant read 1000000 byte",sizeof(a));
				exit(-1);
			}

			n = write(dest,&buff,1000000);
			if(n!=1000000)
			{
				char a[]="cant read 1000000 byte";
				write(1,"cant read 1000000 byte",sizeof(a));
				exit(-1);
			}
			filesize-=1000000;
		}
		if(filesize>0)
		{
			lseek(source,(off_t)0,SEEK_SET);
			char buff1[1000000];
			n=read(source,buff1,filesize);
			for(i=filesize-1;i>=0;i--)
			{
				if(buff1[i]>64&&buff1[i]<91)
				{
					buff1[i]+=32;
				}
				else if(buff1[i]>96&&buff1[i]<123)
				{
					buff1[i]-=32;
				}
			}
			if(n!=filesize)
			{
				char a[]="cant read 10 byte";
				write(1,"cant read 10 byte",sizeof(a));
				exit(-1);
			}

			n = write(dest,&buff1,filesize);
			if(n!=filesize)
			{
				char a[]="cant read 1000000 byte";
				write(1,"cant read 1000000 byte",sizeof(a));
				exit(-1);
			}
		}
	}


	else{

		for (i = filesize-2; i >= 0; i--) { 
			lseek(source, (off_t) i, SEEK_SET);

			n = read(source, &buf, 1);
			if(buf>='A' && buf <='Z')
				buf +=32;
			else if(buf>='a' && buf <='z')
				buf -=32;
			if (n != 1) {
				write(1,"cant read 1 byte",16);
				exit(-1);
			}

			n = write(dest, &buf, 1);

			if (n != 1) {
				write(1,"cant write 1 byte",17);
				exit(-1);
			}

		}
	}
	close(source);
	close(dest);

	int ret; 
	if(ret=(symlink("Assignment/dest.txt","link.txt"))<0)
	{
		write(1,"symlink not created",19);
		exit(-1);
	}
	struct stat dir,file,symlink;

	stat("Assignment",&dir);

	if(S_ISDIR(dir.st_mode))
		write(1,"Checking whether the directory has been created: Yes\n",55);
	else
		write(1,"Checking whether the directory has been created: No\n",54);

	stat("Assignment/dest.txt",&file);

	if(S_ISREG(file.st_mode))
		write(1,"Checking whether the file has been created: Yes\n",50);
	else
		write(1,"Checking whether the file has been created: No\n",49);

	lstat("link.txt",&symlink);

	if(S_ISLNK(symlink.st_mode))
		write(1,"Checking whether the symlink has been created: Yes\n",53);
	else
		write(1,"Checking whether the symlink has been created: No\n",52);

	char e,f;
	int fd1=open(argv[1],O_RDONLY);
	int fd2=open("link.txt",O_RDONLY);
	int flag=1;
	j=0;int k=0;
	char string2;
	int size = resize-2;
	while(size>=1000000)
	{
		lseek(fd1,(off_t)size-1000000,SEEK_SET);
		lseek(fd2,(off_t)size-1000000,SEEK_SET);
		char b1[1000000],b2[1000000];
		n = read(fd1,b1,1000000);
		n = read(fd2,b2,1000000);
		for(i=99999;i>=0;i--)
		{
			if(b1[i]>64&&b1[i]<91)b1[i]+=32;
			else if(b1[i]>96&&b1[i]<123)b1[i]-=32;
			if(b1[i]!=b2[i])
				flag=1;
		}
		size-=1000000;
	}
	if(size>0)
	{
		lseek(fd1,(off_t)0,SEEK_SET);
		lseek(fd2,(off_t)0,SEEK_SET);
		char b3[1000000],b4[1000000];
		n = read(fd1,b3,size);
		n = read(fd2,b4,size);
		for(i=size-1;i>=0;i--)
		{
		if(b3[i]>=65&&b3[i]<=90)
			b3[i]+=32;
		else if(b3[i]>=97&&b3[i]<=122)
			b3[i]-=32;
		if(b3[i]!=b4[i])
			flag=1;
		}
	}
	if(flag==1)
		write(1,"Checking whether file contents have been reversed and case-inverted: Yes\n",75);
	else
		write(1,"Checking whether file contents have been reversed and case-inverted: No\n",74);

	if(S_IRUSR & file.st_mode)
		write(1,"User has read permission on file: Yes\n",40);
	else
		write(1,"User has read permission on file: No\n",39);


	if(S_IWUSR & file.st_mode)
		write(1,"User has write permission on file: Yes\n",39);
	else
		write(1,"User has write permission on file: No\n",38);


	if(S_IXUSR & file.st_mode)
		write(1,"User has execute permission on file: Yes\n",41);
	else
		write(1,"User has execute permission on file: No\n",40);




	if(S_IRGRP & file.st_mode)
		write(1,"Group has read permission on file: Yes\n",39);
	else
		write(1,"Group has read permission on file: No\n",38);


	if(S_IWGRP & file.st_mode)
		write(1,"Group has write permission on file: Yes\n",40);
	else
		write(1,"Group has write permission on file: No\n",39);


	if(S_IXGRP & file.st_mode)
		write(1,"Group has execute permission on file: Yes\n",42);
	else
		write(1,"Group has execute permission on file: No\n",41);






	if(S_IROTH & file.st_mode)
		write(1,"Others has read permission on file: Yes\n",40);
	else
		write(1,"Others has read permission on file: No\n",39);


	if(S_IWOTH & file.st_mode)
		write(1,"Others has write permission on file: Yes\n",41);
	else
		write(1,"Others has write permission on file: No\n",40);


	if(S_IXOTH & file.st_mode)
		write(1,"Others has execute permission on file: Yes\n",43);
	else
		write(1,"Others has execute permission on file: No\n",42);







	if(S_IRUSR & dir.st_mode)
		write(1,"User has read permission on directory: Yes\n",45);
	else
		write(1,"User has read permission on directory: No\n",44);


	if(S_IWUSR & dir.st_mode)
		write(1,"User has write permission on directory: Yes\n",44);
	else
		write(1,"User has write permission on directory: No\n",43);


	if(S_IXUSR & dir.st_mode)
		write(1,"User has execute permission on directory: Yes\n",46);
	else
		write(1,"User has execute permission on directory: No\n",45);




	if(S_IRGRP & dir.st_mode)
		write(1,"Group has read permission on directory: Yes\n",44);
	else
		write(1,"Group has read permission on directory: No\n",43);


	if(S_IWGRP & dir.st_mode)
		write(1,"Group has write permission on directory: Yes\n",45);
	else
		write(1,"Group has write permission on directory: No\n",44);


	if(S_IXGRP & dir.st_mode)
		write(1,"Group has execute permission on directory: Yes\n",47);
	else
		write(1,"Group has execute permission on directory: No\n",46);



	if(S_IROTH & dir.st_mode)
		write(1,"Others has read permission on directory: Yes\n",45);
	else
		write(1,"Others has read permission on directory: No\n",44);

	if(S_IWOTH & dir.st_mode)

		write(1,"Others has write permission on directory: Yes\n",46);
	else
		write(1,"Others has write permission on directory: No\n",45);


	if(S_IXOTH & dir.st_mode)
		write(1,"Others has execute permission on directory: Yes\n",48);
	else
		write(1,"Others has execute permission on directory: No\n",47);
	close(fd1);
	close(fd2);


	return 0;
}
