#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "AdjList.h"
#include <QMessageBox>
#include <string>
#include <vector>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->song1->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    ui->song1->setOpenExternalLinks(true);
    ui->song1->setTextFormat(Qt::RichText);
    ui->song2->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    ui->song2->setOpenExternalLinks(true);
    ui->song2->setTextFormat(Qt::RichText);
    ui->song3->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    ui->song3->setOpenExternalLinks(true);
    ui->song3->setTextFormat(Qt::RichText);
    ui->song4->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    ui->song4->setOpenExternalLinks(true);
    ui->song4->setTextFormat(Qt::RichText);
    ui->song5->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    ui->song5->setOpenExternalLinks(true);
    ui->song5->setTextFormat(Qt::RichText);
    ui->song6->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    ui->song6->setOpenExternalLinks(true);
    ui->song6->setTextFormat(Qt::RichText);
    ui->song7->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    ui->song7->setOpenExternalLinks(true);
    ui->song7->setTextFormat(Qt::RichText);
    ui->song8->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    ui->song8->setOpenExternalLinks(true);
    ui->song8->setTextFormat(Qt::RichText);
    ui->song9->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    ui->song9->setOpenExternalLinks(true);
    ui->song9->setTextFormat(Qt::RichText);
    ui->song10->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    ui->song10->setOpenExternalLinks(true);
    ui->song10->setTextFormat(Qt::RichText);

}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::returnLink(string song){
    string word = "";
    vector<string> words;
    for (auto letter : song)
    {
        if (letter == ' ')
        {
            words.push_back(word);
            word = "";
        }
        else {
            word = word + letter;
        }
    }
    words.push_back(word);

    string link = "/search?q=";
    for(auto iter = words.begin(); iter != words.end(); iter++){
        if ((iter + 1) == words.end()){
            link = link + *iter + "\">";
        }
        else{
            link = link + *iter + "+";
        }
    }

    QString first = "<a href=\"http://google.com" ;
    QString insertLink = QString::fromStdString(link);
    QString insert = first + insertLink + QString::fromStdString(song) + "</a>";
    return insert;
}

void MainWindow::on_songSearchButton_clicked()
{
    QString searchedSong = ui->songSearch->text();
    string insertSong = searchedSong.toStdString();
    ui->messageOutput->setText("");
    ui->songSearch->setText("");
    ui->compareOne->setText("");
    ui->compareTwo->setText("");

    vector<string> songs = g.makePlaylist(insertSong); //Assign with returned vector of similar songs;

    if (songs.empty() == true){ //
        //QMessageBox::warning(this,"Error", "Song Does Not Exist in Database");
        ui->playlistLabel->setText("");
        ui->messageOutput->setStyleSheet("QLabel{color: red}");
        ui->messageOutput->setText("Song Does Not Exist in Database");
        ui->song1->setText("");
        ui->song2->setText("");
        ui->song3->setText("");
        ui->song4->setText("");
        ui->song5->setText("");
        ui->song6->setText("");
        ui->song7->setText("");
        ui->song8->setText("");
        ui->song9->setText("");
        ui->song10->setText("");
    }
    else{
        ui->playlistLabel->setText("Playlist Suggestions");
        ui->song1->setText("1. " + returnLink(songs.at(0)));
        ui->song2->setText("2. " + returnLink(songs.at(1)));
        ui->song3->setText("3. " + returnLink(songs.at(2)));
        ui->song4->setText("4. " + returnLink(songs.at(3)));
        ui->song5->setText("5. " + returnLink(songs.at(4)));
        ui->song6->setText("6. " + returnLink(songs.at(5)));
        ui->song7->setText("7. " + returnLink(songs.at(6)));
        ui->song8->setText("8. " + returnLink(songs.at(7)));
        ui->song9->setText("9. " + returnLink(songs.at(8)));
        ui->song10->setText("10. " + returnLink(songs.at(9)));
    }
}

void MainWindow::on_shuffleButton_clicked()
{
    string randomSong = g.shuffle();
    vector<string> songs = g.makePlaylist(randomSong);//Get Vector

    ui->messageOutput->setText("");
    ui->playlistLabel->setText("Playlist Suggestions");
    ui->song1->setText("1. " + returnLink(songs.at(0)));
    ui->song2->setText("2. " + returnLink(songs.at(1)));
    ui->song3->setText("3. " + returnLink(songs.at(2)));
    ui->song4->setText("4. " + returnLink(songs.at(3)));
    ui->song5->setText("5. " + returnLink(songs.at(4)));
    ui->song6->setText("6. " + returnLink(songs.at(5)));
    ui->song7->setText("7. " + returnLink(songs.at(6)));
    ui->song8->setText("8. " + returnLink(songs.at(7)));
    ui->song9->setText("9. " + returnLink(songs.at(8)));
    ui->song10->setText("10. " + returnLink(songs.at(9)));

    cout << "Vertices: " << "109530" << endl; //
}


void MainWindow::on_compareButton_clicked()
{
    QString firstSong = ui->compareOne->text();
    QString secondSong = ui->compareTwo->text();
    string songOne = firstSong.toStdString();
    string songTwo = secondSong.toStdString();
    ui->messageOutput->setText("");
    ui->compareOne->setText("");
    ui->compareTwo->setText("");
    ui->songSearch->setText("");

    if (g.isRelatedBFS(songOne, songTwo) == true){
        ui->messageOutput->setStyleSheet("QLabel{color: black}");
        ui->messageOutput->setText("Songs are Related");
    }
    else{
        ui->messageOutput->setStyleSheet("QLabel{color: black}");
        ui->messageOutput->setText("Songs are not Related");
    }

    cout << "Time Comparison" << endl;
    chrono::time_point < chrono::system_clock > start,end;
    start = chrono::system_clock::now();
    g.isRelatedBFS(songOne, songTwo);
    end = chrono::system_clock::now();
    chrono::duration < double > timeTakenBFS = end - start;
    cout << "Time Taken for BFS Search: " << timeTakenBFS.count() << " seconds." << endl;

    start = chrono::system_clock::now();
    g.isRelatedDFS(songOne, songTwo);
    end = chrono::system_clock::now();
    chrono::duration < double > timeTakenDFS = end - start;
    cout << "Time Taken for DFS Search: " << timeTakenDFS.count() << " seconds." << endl;
}

