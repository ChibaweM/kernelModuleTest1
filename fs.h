struct file_operations {
	struct module *owner;
	ssize_t (*read) (struct file *, char user *, size_t, loff_t *);
	ssize_t(*write) (struct file *, const char *, size_t, loff_t *);
};
