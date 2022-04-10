# oostubs
Please note that we don't allow working directly on the master branch. The new feature should be implemented on other branches and merged to master after test and team review.

## Hint for Git
### How to get update from official repo
```
#git remote add upstream https://os.inf.tu-dresden.de/Studium/OSC/SS2022/oostubs.git
 git pull upstream main
```

### How to squash commits after they have been pushed
```
git rebase -i origin/brach_name~4 brach_name
git push origin +master

```
If you just want it to download the changes without automatically merging, use git fetch instead of git pull.
