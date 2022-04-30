# oostubs
Please note that we don't allow working directly on the master branch. The new feature should be implemented on other branches and merged to master after test and team review.

## Hint for Git
### How to get update from official repo
```
#git remote add upstream https://os.inf.tu-dresden.de/Studium/OSC/SS2022/oostubs.git
 git pull upstream main
```
If you just want it to download the changes without automatically merging, use git fetch instead of git pull.
### How to squash commits after they have been pushed
```
git rebase -i origin/branch_name~4 branch_name
git push origin +branch_name

```
## How to run oostubs
+ Compile oostubs
```
make
```
+ Execute oostubs
```
make qemu
```
+ Debug oostubs
```
make qemu-gdb

make gdb
```
+ Reference project
```
https://github.com/00mjk/oostubs/blob/ff874e893e6a91a5129f6f7609ae4f4ac0ca0947/loesung/user/appl.cc
```
