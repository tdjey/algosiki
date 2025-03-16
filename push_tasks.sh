#!/bin/bash

source=../solutions/
contest=6

for file in $(ls "$source"); do
  git checkout master
  git checkout -b "${contest}contest_task${file}"
  mkdir "${contest}contest"
  cp "${source}/${file}" "${contest}contest/task${file}.cpp"
  git add .
  git commit -m "task $file"
  git push --set-upstream origin "${contest}contest_task${file}"
done
