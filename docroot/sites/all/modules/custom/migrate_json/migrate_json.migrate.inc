<?php

class JSONMigration extends Migration {

/**
 * Abstract constructor
 * @param unknown $arguments
 */
  public function __construct($arguments); {
    parent::__construct($arguments);
    $this->description = t('A custom JSON import module for DNA'),
    //$item_url = xxx ;
    //$list_url = xxx ;
    $fields = array(
    	'UID' => 'User ID',
      'first_name' => 'Users First Name',
      'last_name' => 'Users surname',

    )
  //Define the source
  $this->source = new MigrateSourceList(
      new MigrateSourceJSON($list_url),
      new MigrateItemJSON($item_url, array()),
      $fields
    );
  //Define map
  //TODO: Check how much I can map or if I need mult-fn.
  $this->map = new MigrateSQLMap($this->machineName,
    array(
  	  'name' => array(
  	     'type' => '',
  	     'not_null' => TRUE,
         ),
      'gender' => array(
  	  	'type' => 'string'
  	  )
    ),
    MigrateDestinationUser::getKeySchema()
  );

  //Define the destination
  $this->destination = new MigrateDestinationUser();
  //Define the mapping
  $this->


  }

}