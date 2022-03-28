gofmt -w *.go
goimports -w *.go

uncrustify -c ./etc/uncrustify.cfg --replace */*.c */*.h src/*.c *.c *.h
shfmt -w *.sh
find . -name "*.unc-backup*" -type f | xargs -I % unlink %
